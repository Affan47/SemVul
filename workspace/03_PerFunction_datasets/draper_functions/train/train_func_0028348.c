sec_from_timer_a(u8 *secs, u8 taq, u8 timer_a)
{
	if (taq != ABB5ZES3_REG_TIMA_CLK_TAQ1)
		return -EINVAL;

	*secs = timer_a;

	return 0;
}
