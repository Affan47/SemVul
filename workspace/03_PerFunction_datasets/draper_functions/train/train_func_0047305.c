nfsd4_umh_cltrack_init(struct net *net)
{
	int ret;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	char *grace_start = nfsd4_cltrack_grace_start(nn->boot_time);


	if (net != &init_net) {
		pr_warn("NFSD: attempt to initialize umh client tracking in a container ignored.\n");
		return -EINVAL;
	}

	ret = nfsd4_umh_cltrack_upcall("init", NULL, grace_start, NULL);
	kfree(grace_start);
	return ret;
}
