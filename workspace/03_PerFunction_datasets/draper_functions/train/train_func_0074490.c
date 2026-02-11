treble_eq( blip_eq_t const& eq )
{
	float fimpulse [blip_res / 2 * (blip_widest_impulse_ - 1) + blip_res * 2];

	int const half_size = blip_res / 2 * (width - 1);
	eq.generate( &fimpulse [blip_res], half_size );

	int i;


	for ( i = blip_res; i--; )
		fimpulse [blip_res + half_size + i] = fimpulse [blip_res + half_size - 1 - i];


	for ( i = 0; i < blip_res; i++ )
		fimpulse [i] = 0.0f;


	double total = 0.0;
	for ( i = 0; i < half_size; i++ )
		total += fimpulse [blip_res + i];


	double const base_unit = 32768.0;
	double rescale = base_unit / 2 / total;
	kernel_unit = (long) base_unit;


	double sum = 0.0;
	double next = 0.0;
	int const impulses_size = this->impulses_size();
	for ( i = 0; i < impulses_size; i++ )
	{
		impulses [i] = (short) floor( (next - sum) * rescale + 0.5 );
		sum += fimpulse [i];
		next += fimpulse [i + blip_res];
	}
	adjust_impulse();


	double vol = volume_unit_;
	if ( vol )
	{
		volume_unit_ = 0.0;
		volume_unit( vol );
	}
}
