nfs4_set_client(struct nfs_server *server,
		const char *hostname,
		const struct sockaddr *addr,
		const size_t addrlen,
		const char *ip_addr,
		rpc_authflavor_t authflavour,
		int proto, const struct rpc_timeout *timeparms,
		u32 minorversion, struct net *net)
{
	struct nfs_client_initdata cl_init = {
		.hostname = hostname,
		.addr = addr,
		.addrlen = addrlen,
		.nfs_mod = &nfs_v4,
		.proto = proto,
		.minorversion = minorversion,
		.net = net,
	};
	struct nfs_client *clp;
	int error;

	dprintk("--> nfs4_set_client()\n");

	if (server->flags & NFS_MOUNT_NORESVPORT)
		set_bit(NFS_CS_NORESVPORT, &cl_init.init_flags);
	if (server->options & NFS_OPTION_MIGRATION)
		set_bit(NFS_CS_MIGRATION, &cl_init.init_flags);


	clp = nfs_get_client(&cl_init, timeparms, ip_addr, authflavour);
	if (IS_ERR(clp)) {
		error = PTR_ERR(clp);
		goto error;
	}


	set_bit(NFS_CS_CHECK_LEASE_TIME, &clp->cl_res_state);

	server->nfs_client = clp;
	dprintk("<-- nfs4_set_client() = 0 [new %p]\n", clp);
	return 0;
error:
	dprintk("<-- nfs4_set_client() = xerror %d\n", error);
	return error;
}
