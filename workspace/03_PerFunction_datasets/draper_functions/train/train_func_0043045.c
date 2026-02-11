nfsd4_shutdown_recdir(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	if (!nn->rec_file)
		return;
	fput(nn->rec_file);
	nn->rec_file = NULL;
}
