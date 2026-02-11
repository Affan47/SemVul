debug_stack_reset(void)
{
	if (WARN_ON(!this_cpu_read(debug_idt_ctr)))
		return;
	if (this_cpu_dec_return(debug_idt_ctr) == 0)
		load_current_idt();
}
