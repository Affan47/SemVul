_remove_device_opp(struct device_opp *dev_opp)
{
	struct device_list_opp *list_dev;

	if (!list_empty(&dev_opp->opp_list))
		return;

	list_dev = list_first_entry(&dev_opp->dev_list, struct device_list_opp,
				    node);

	_remove_list_dev(list_dev, dev_opp);


	WARN_ON(!list_empty(&dev_opp->dev_list));

	list_del_rcu(&dev_opp->node);
	call_srcu(&dev_opp->srcu_head.srcu, &dev_opp->rcu_head,
		  _kfree_device_rcu);
}
