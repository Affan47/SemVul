calc_amp() const
{
	int amp = phase_range - phase;
	if ( amp < 0 )
		amp = phase - (phase_range + 1);
	return amp;
}
