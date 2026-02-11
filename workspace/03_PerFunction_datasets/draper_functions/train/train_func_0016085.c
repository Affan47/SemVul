o2net_complete_nsw_locked(struct o2net_node *nn,
				      struct o2net_status_wait *nsw,
				      enum o2net_system_error sys_status,
				      s32 status)
{
	assert_spin_locked(&nn->nn_lock);

	if (!list_empty(&nsw->ns_node_item)) {
		list_del_init(&nsw->ns_node_item);
		nsw->ns_sys_status = sys_status;
		nsw->ns_status = status;
		idr_remove(&nn->nn_status_idr, nsw->ns_id);
		wake_up(&nsw->ns_wq);
	}
}
