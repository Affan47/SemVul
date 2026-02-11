nfsd4_cld_unregister_net(struct net *net, struct rpc_pipe *pipe)
{
	struct super_block *sb;

	sb = rpc_get_sb_net(net);
	if (sb) {
		nfsd4_cld_unregister_sb(pipe);
		rpc_put_sb_net(net);
	}
}
