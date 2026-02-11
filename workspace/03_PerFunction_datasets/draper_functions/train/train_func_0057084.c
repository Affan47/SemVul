nfs_umount(const struct nfs_mount_request *info)
{
	static const struct rpc_timeout nfs_umnt_timeout = {
		.to_initval = 1 * HZ,
		.to_maxval = 3 * HZ,
		.to_retries = 2,
	};
	struct rpc_create_args args = {
		.net		= info->net,
		.protocol	= IPPROTO_UDP,
		.address	= info->sap,
		.addrsize	= info->salen,
		.timeout	= &nfs_umnt_timeout,
		.servername	= info->hostname,
		.program	= &mnt_program,
		.version	= info->version,
		.authflavor	= RPC_AUTH_UNIX,
		.flags		= RPC_CLNT_CREATE_NOPING,
	};
	struct rpc_message msg	= {
		.rpc_argp	= info->dirpath,
	};
	struct rpc_clnt *clnt;
	int status;

	if (strlen(info->dirpath) > MNTPATHLEN)
		return;

	if (info->noresvport)
		args.flags |= RPC_CLNT_CREATE_NONPRIVPORT;

	clnt = rpc_create(&args);
	if (IS_ERR(clnt))
		goto out_clnt_err;

	dprintk("NFS: sending UMNT request for %s:%s\n",
		(info->hostname ? info->hostname : "server"), info->dirpath);

	if (info->version == NFS_MNT3_VERSION)
		msg.rpc_proc = &clnt->cl_procinfo[MOUNTPROC3_UMNT];
	else
		msg.rpc_proc = &clnt->cl_procinfo[MOUNTPROC_UMNT];

	status = rpc_call_sync(clnt, &msg, 0);
	rpc_shutdown_client(clnt);

	if (unlikely(status < 0))
		goto out_call_err;

	return;

out_clnt_err:
	dprintk("NFS: failed to create UMNT RPC client, status=%ld\n",
			PTR_ERR(clnt));
	return;

out_call_err:
	dprintk("NFS: UMNT request failed, status=%d\n", status);
}
