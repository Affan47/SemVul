nfs_submount(struct nfs_server *server, struct dentry *dentry,
			      struct nfs_fh *fh, struct nfs_fattr *fattr)
{
	int err;
	struct dentry *parent = dget_parent(dentry);


	err = server->nfs_client->rpc_ops->lookup(d_inode(parent), &dentry->d_name, fh, fattr, NULL);
	dput(parent);
	if (err != 0)
		return ERR_PTR(err);

	return nfs_do_submount(dentry, fh, fattr, server->client->cl_auth->au_flavor);
}
