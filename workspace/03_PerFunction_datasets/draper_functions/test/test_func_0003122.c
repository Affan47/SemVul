CALC_FCSLOT(OPL_CH *CH,OPL_SLOT *SLOT)
{
	int ksr;


	SLOT->Incr = CH->fc * SLOT->mul;
	ksr = CH->kcode >> SLOT->KSR;

	if( SLOT->ksr != ksr )
	{
		SLOT->ksr = ksr;


		if ((SLOT->ar + SLOT->ksr) < 16+62)
		{
			SLOT->eg_sh_ar  = eg_rate_shift [SLOT->ar + SLOT->ksr ];
			SLOT->eg_sel_ar = eg_rate_select[SLOT->ar + SLOT->ksr ];
		}
		else
		{
			SLOT->eg_sh_ar  = 0;
			SLOT->eg_sel_ar = 13*RATE_STEPS;
		}
		SLOT->eg_sh_dr  = eg_rate_shift [SLOT->dr + SLOT->ksr ];
		SLOT->eg_sel_dr = eg_rate_select[SLOT->dr + SLOT->ksr ];
		SLOT->eg_sh_rr  = eg_rate_shift [SLOT->rr + SLOT->ksr ];
		SLOT->eg_sel_rr = eg_rate_select[SLOT->rr + SLOT->ksr ];
	}
}
