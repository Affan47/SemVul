nfs_cb_idr_remove_locked(struct nfs_client *clp)
{
	struct nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);

	if (clp->cl_cb_ident)
		idr_remove(&nn->cb_ident_idr, clp->cl_cb_ident);
}
