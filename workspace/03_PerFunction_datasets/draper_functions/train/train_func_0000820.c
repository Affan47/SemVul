nfsd4_check_legacy_client(struct nfs4_client *clp)
{
	int status;
	char dname[HEXDIR_LEN];
	struct nfs4_client_reclaim *crp;
	struct nfsd_net *nn = net_generic(clp->net, nfsd_net_id);


	if (test_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags))
		return 0;

	status = nfs4_make_rec_clidname(dname, &clp->cl_name);
	if (status) {
		legacy_recdir_name_error(clp, status);
		return status;
	}


	crp = nfsd4_find_reclaim_client(dname, nn);
	if (crp) {
		set_bit(NFSD4_CLIENT_STABLE, &clp->cl_flags);
		crp->cr_clp = clp;
		return 0;
	}

	return -ENOENT;
}
