_opp_remove(struct device_opp *dev_opp,
			struct dev_pm_opp *opp, bool notify)
{


	if (notify)
		srcu_notifier_call_chain(&dev_opp->srcu_head, OPP_EVENT_REMOVE, opp);
	list_del_rcu(&opp->node);
	call_srcu(&dev_opp->srcu_head.srcu, &opp->rcu_head, _kfree_opp_rcu);

	_remove_device_opp(dev_opp);
}
