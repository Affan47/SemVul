nfs3_clone_server(struct nfs_server *source,
				     struct nfs_fh *fh,
				     struct nfs_fattr *fattr,
				     rpc_authflavor_t flavor)
{
	struct nfs_server *server = nfs_clone_server(source, fh, fattr, flavor);
	if (!IS_ERR(server) && !IS_ERR(source->client_acl))
		nfs_init_server_aclclient(server);
	return server;
}
