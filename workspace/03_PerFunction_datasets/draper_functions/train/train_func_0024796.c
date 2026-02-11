attach_ulds(struct adapter *adap)
{
	unsigned int i;

	spin_lock(&adap_rcu_lock);
	list_add_tail_rcu(&adap->rcu_node, &adap_rcu_list);
	spin_unlock(&adap_rcu_lock);

	mutex_lock(&uld_mutex);
	list_add_tail(&adap->list_node, &adapter_list);
	for (i = 0; i < CXGB4_ULD_MAX; i++)
		if (ulds[i].add)
			uld_attach(adap, i);
	mutex_unlock(&uld_mutex);
}
