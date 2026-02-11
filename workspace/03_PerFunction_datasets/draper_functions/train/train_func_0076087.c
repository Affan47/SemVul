vub300_inactivity_timer_expired(unsigned long data)
{
	struct vub300_mmc_host *vub300 = (struct vub300_mmc_host *)data;
	if (!vub300->interface) {
		kref_put(&vub300->kref, vub300_delete);
	} else if (vub300->cmd) {
		mod_timer(&vub300->inactivity_timer, jiffies + HZ);
	} else {
		vub300_queue_dead_work(vub300);
		mod_timer(&vub300->inactivity_timer, jiffies + HZ);
	}
}
