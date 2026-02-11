nicvf_rbdr_task(unsigned long data)
{
	struct nicvf *nic = (struct nicvf *)data;

	nicvf_refill_rbdr(nic, GFP_ATOMIC);
	if (nic->rb_alloc_fail) {
		nic->rb_work_scheduled = true;
		schedule_delayed_work(&nic->rbdr_work, msecs_to_jiffies(10));
	}
}
