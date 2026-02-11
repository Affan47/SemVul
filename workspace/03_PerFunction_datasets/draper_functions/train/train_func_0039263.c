torture_must_stop_irq(void)
{
	return READ_ONCE(fullstop) != FULLSTOP_DONTSTOP;
}
