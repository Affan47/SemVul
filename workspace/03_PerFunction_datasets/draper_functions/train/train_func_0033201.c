nfs4_create_referral_server(struct nfs_clone_mount *data,
					       struct nfs_fh *mntfh)
{
	struct nfs_client *parent_client;
	struct nfs_server *server, *parent_server;
	bool auth_probe;
	int error;

	dprintk("--> nfs4_create_referral_server()\n");

	server = nfs_alloc_server();
	if (!server)
		return ERR_PTR(-ENOMEM);

	parent_server = NFS_SB(data->sb);
	parent_client = parent_server->nfs_client;


	nfs_server_copy_userdata(server, parent_server);


	error = nfs4_set_client(server, data->hostname,
				data->addr,
				data->addrlen,
				parent_client->cl_ipaddr,
				data->authflavor,
				rpc_protocol(parent_server->client),
				parent_server->client->cl_timeout,
				parent_client->cl_mvops->minor_version,
				parent_client->cl_net);
	if (error < 0)
		goto error;

	error = nfs_init_server_rpcclient(server, parent_server->client->cl_timeout, data->authflavor);
	if (error < 0)
		goto error;

	auth_probe = parent_server->auth_info.flavor_len < 1;

	error = nfs4_server_common_setup(server, mntfh, auth_probe);
	if (error < 0)
		goto error;

	dprintk("<-- nfs_create_referral_server() = %p\n", server);
	return server;

error:
	nfs_free_server(server);
	dprintk("<-- nfs4_create_referral_server() = error %d\n", error);
	return ERR_PTR(error);
}
