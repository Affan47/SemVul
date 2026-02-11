nfs_proc_create(struct inode *dir, struct dentry *dentry, struct iattr *sattr,
		int flags)
{
	struct nfs_createdata *data;
	struct rpc_message msg = {
		.rpc_proc	= &nfs_procedures[NFSPROC_CREATE],
	};
	int status = -ENOMEM;

	dprintk("NFS call  create %pd\n", dentry);
	data = nfs_alloc_createdata(dir, dentry, sattr);
	if (data == NULL)
		goto out;
	msg.rpc_argp = &data->arg;
	msg.rpc_resp = &data->res;
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_for_revalidate(dir);
	if (status == 0)
		status = nfs_instantiate(dentry, data->res.fh, data->res.fattr, NULL);
	nfs_free_createdata(data);
out:
	dprintk("NFS reply create: %d\n", status);
	return status;
}
