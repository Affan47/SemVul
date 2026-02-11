grace_exit_net(struct net *net)
{
	struct list_head *grace_list = net_generic(net, grace_net_id);

	BUG_ON(!list_empty(grace_list));
}
