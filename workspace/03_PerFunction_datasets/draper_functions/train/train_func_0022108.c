next_request(int err)
{
	unsigned long saved_flags;

	spin_lock_irqsave(&pf_spin_lock, saved_flags);
	pf_end_request(err);
	pf_busy = 0;
	do_pf_request(pf_queue);
	spin_unlock_irqrestore(&pf_spin_lock, saved_flags);
}
