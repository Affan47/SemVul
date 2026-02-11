join_handler(int status, struct ib_sa_mcmember_rec *rec,
			 void *context)
{
	struct mcast_group *group = context;
	u16 pkey_index = MCAST_INVALID_PKEY_INDEX;

	if (status)
		process_join_error(group, status);
	else {
		int mgids_changed, is_mgid0;

		if (ib_find_pkey(group->port->dev->device,
				 group->port->port_num, be16_to_cpu(rec->pkey),
				 &pkey_index))
			pkey_index = MCAST_INVALID_PKEY_INDEX;

		spin_lock_irq(&group->port->lock);
		if (group->state == MCAST_BUSY &&
		    group->pkey_index == MCAST_INVALID_PKEY_INDEX)
			group->pkey_index = pkey_index;
		mgids_changed = memcmp(&rec->mgid, &group->rec.mgid,
				       sizeof(group->rec.mgid));
		group->rec = *rec;
		if (mgids_changed) {
			rb_erase(&group->node, &group->port->table);
			is_mgid0 = !memcmp(&mgid0, &group->rec.mgid,
					   sizeof(mgid0));
			mcast_insert(group->port, group, is_mgid0);
		}
		spin_unlock_irq(&group->port->lock);
	}
	mcast_work_handler(&group->work);
}
