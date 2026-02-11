sel_netif_destroy(struct sel_netif *netif)
{
	list_del_rcu(&netif->list);
	sel_netif_total--;
	kfree_rcu(netif, rcu_head);
}
