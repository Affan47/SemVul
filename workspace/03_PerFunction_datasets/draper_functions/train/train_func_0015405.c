nfsd_last_thread(struct svc_serv *serv, struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);


	if (!nn->nfsd_net_up)
		return;
	nfsd_shutdown_net(net);

	svc_rpcb_cleanup(serv, net);

	printk(KERN_WARNING "nfsd: last server has exited, flushing export "
			    "cache\n");
	nfsd_export_flush(net);
}
