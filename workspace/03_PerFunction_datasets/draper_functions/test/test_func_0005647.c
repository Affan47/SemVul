uwb_rsv_sched_update(struct uwb_rc *rc)
{
	spin_lock_irq(&rc->rsvs_lock);
	if (!delayed_work_pending(&rc->rsv_update_work)) {
		if (rc->set_drp_ie_pending > 0) {
			rc->set_drp_ie_pending++;
			goto unlock;
		}
		uwb_rsv_queue_update(rc);
	}
unlock:
	spin_unlock_irq(&rc->rsvs_lock);
}
