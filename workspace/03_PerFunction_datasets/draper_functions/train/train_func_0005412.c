proc_net_ns_init(struct net *net)
{
	struct proc_dir_entry *netd, *net_statd;
	int err;

	err = -ENOMEM;
	netd = kzalloc(sizeof(*netd) + 4, GFP_KERNEL);
	if (!netd)
		goto out;

	netd->subdir = RB_ROOT;
	netd->data = net;
	netd->nlink = 2;
	netd->namelen = 3;
	netd->parent = &proc_root;
	memcpy(netd->name, "net", 4);

	err = -EEXIST;
	net_statd = proc_net_mkdir(net, "stat", netd);
	if (!net_statd)
		goto free_net;

	net->proc_net = netd;
	net->proc_net_stat = net_statd;
	return 0;

free_net:
	kfree(netd);
out:
	return err;
}
