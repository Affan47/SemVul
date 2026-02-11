dln2_run_event_callbacks(struct dln2_dev *dln2, u16 id, u16 echo,
				     void *data, int len)
{
	struct dln2_event_cb_entry *i;

	rcu_read_lock();

	list_for_each_entry_rcu(i, &dln2->event_cb_list, list) {
		if (i->id == id) {
			i->callback(i->pdev, echo, data, len);
			break;
		}
	}

	rcu_read_unlock();
}
