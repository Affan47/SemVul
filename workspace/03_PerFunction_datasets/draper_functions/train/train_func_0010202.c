showacpu(void *dummy)
{
	unsigned long flags;


	if (idle_cpu(smp_processor_id()))
		return;

	spin_lock_irqsave(&show_lock, flags);
	pr_info("CPU%d:\n", smp_processor_id());
	show_stack(NULL, NULL);
	spin_unlock_irqrestore(&show_lock, flags);
}
