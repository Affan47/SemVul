nfsd4_init_cld_pipe(struct net *net)
{
	int ret;
	struct dentry *dentry;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	struct cld_net *cn;

	if (nn->cld_net)
		return 0;

	cn = kzalloc(sizeof(*cn), GFP_KERNEL);
	if (!cn) {
		ret = -ENOMEM;
		goto err;
	}

	cn->cn_pipe = rpc_mkpipe_data(&cld_upcall_ops, RPC_PIPE_WAIT_FOR_OPEN);
	if (IS_ERR(cn->cn_pipe)) {
		ret = PTR_ERR(cn->cn_pipe);
		goto err;
	}
	spin_lock_init(&cn->cn_lock);
	INIT_LIST_HEAD(&cn->cn_list);

	dentry = nfsd4_cld_register_net(net, cn->cn_pipe);
	if (IS_ERR(dentry)) {
		ret = PTR_ERR(dentry);
		goto err_destroy_data;
	}

	cn->cn_pipe->dentry = dentry;
	nn->cld_net = cn;
	return 0;

err_destroy_data:
	rpc_destroy_pipe_data(cn->cn_pipe);
err:
	kfree(cn);
	printk(KERN_ERR "NFSD: unable to create nfsdcld upcall pipe (%d)\n",
			ret);
	return ret;
}
