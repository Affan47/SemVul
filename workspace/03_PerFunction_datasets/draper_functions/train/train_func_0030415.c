nfs_find_best_sec(struct rpc_clnt *clnt,
					  struct nfs_server *server,
					  struct nfs4_secinfo_flavors *flavors)
{
	rpc_authflavor_t pflavor;
	struct nfs4_secinfo4 *secinfo;
	unsigned int i;

	for (i = 0; i < flavors->num_flavors; i++) {
		secinfo = &flavors->flavors[i];

		switch (secinfo->flavor) {
		case RPC_AUTH_NULL:
		case RPC_AUTH_UNIX:
		case RPC_AUTH_GSS:
			pflavor = rpcauth_get_pseudoflavor(secinfo->flavor,
							&secinfo->flavor_info);

			if (pflavor != RPC_AUTH_MAXFLAVOR &&
			    nfs_auth_info_match(&server->auth_info, pflavor)) {
				struct rpc_clnt *new;
				struct rpc_cred *cred;


				new = rpc_clone_client_set_auth(clnt, pflavor);
				if (IS_ERR(new))
					continue;


				cred = rpcauth_lookupcred(new->cl_auth, 0);
				if (IS_ERR(cred)) {
					rpc_shutdown_client(new);
					continue;
				}
				put_rpccred(cred);
				return new;
			}
		}
	}
	return ERR_PTR(-EPERM);
}
