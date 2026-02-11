force_int_on(void)
{
	xbarrier();
	suppress_int = 0;
	if (pending_int)
		raise_interrupt();
}
