optimized_callback(struct optimized_kprobe *op, struct pt_regs *regs)
{
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	unsigned long flags;


	if (kprobe_disabled(&op->kp))
		return;

	local_irq_save(flags);
	if (kprobe_running()) {
		kprobes_inc_nmissed_count(&op->kp);
	} else {

#ifdef CONFIG_X86_64
		regs->cs = __KERNEL_CS;
#else
		regs->cs = __KERNEL_CS | get_kernel_rpl();
		regs->gs = 0;
#endif
		regs->ip = (unsigned long)op->kp.addr + INT3_SIZE;
		regs->orig_ax = ~0UL;

		__this_cpu_write(current_kprobe, &op->kp);
		kcb->kprobe_status = KPROBE_HIT_ACTIVE;
		opt_pre_handler(&op->kp, regs);
		__this_cpu_write(current_kprobe, NULL);
	}
	local_irq_restore(flags);
}
