reset()
{
	latch   = 0;
	balance = 0xFF;

	Hes_Osc* osc = &oscs [osc_count];
	do
	{
		osc--;
		memset( osc, 0, offsetof (Hes_Osc,outputs) );
		osc->noise_lfsr = 1;
		osc->control    = 0x40;
		osc->balance    = 0xFF;
	}
	while ( osc != oscs );
}
