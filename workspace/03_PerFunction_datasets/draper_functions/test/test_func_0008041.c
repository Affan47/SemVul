speakup_fake_down_arrow(void)
{
	unsigned long flags;


	local_irq_save(flags);

	preempt_disable();

	__this_cpu_write(reporting_keystroke, true);
	input_report_key(virt_keyboard, KEY_DOWN, PRESSED);
	input_report_key(virt_keyboard, KEY_DOWN, RELEASED);
	input_sync(virt_keyboard);
	__this_cpu_write(reporting_keystroke, false);


	preempt_enable();

	local_irq_restore(flags);
}
