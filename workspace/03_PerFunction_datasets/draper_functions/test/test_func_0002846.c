ymf278b_timer_b_reset(int num)
{
	YMF278BChip *chip = &YMF278B[num];
	if(chip->enable & 2)
	{
		double period = (256-chip->timer_b_count) * 323.1 * chip->clock_ratio;
		timer_adjust(chip->timer_b, TIME_IN_USEC(period), num, TIME_IN_USEC(period));
	}
	else
		timer_adjust(chip->timer_b, TIME_NEVER, num, 0);
}
