YM2151ResetChip(int num)
{
	int i;
	YM2151 *chip = &YMPSG[num];


	for (i=0; i<32; i++)
	{
		memset(&chip->oper[i],'\0',sizeof(YM2151Operator));
		chip->oper[i].volume = MAX_ATT_INDEX;
	}

	chip->eg_timer = 0;
	chip->eg_cnt   = 0;

	chip->lfo_timer  = 0;
	chip->lfo_counter= 0;
	chip->lfo_phase  = 0;
	chip->lfo_wsel   = 0;
	chip->pmd = 0;
	chip->amd = 0;
	chip->lfa = 0;
	chip->lfp = 0;

	chip->test= 0;

	chip->irq_enable = 0;
#ifdef USE_MAME_TIMERS

	timer_enable(chip->timer_A, 0);
	timer_enable(chip->timer_B, 0);
#else
	chip->tim_A      = 0;
	chip->tim_B      = 0;
	chip->tim_A_val  = 0;
	chip->tim_B_val  = 0;
#endif
	chip->timer_A_index = 0;
	chip->timer_B_index = 0;
	chip->timer_A_index_old = 0;
	chip->timer_B_index_old = 0;

	chip->noise     = 0;
	chip->noise_rng = 0;
	chip->noise_p   = 0;
	chip->noise_f   = chip->noise_tab[0];

	chip->csm_req	= 0;
	chip->status    = 0;

	YM2151WriteReg(num, 0x1b, 0);
	YM2151WriteReg(num, 0x18, 0);
	for (i=0x20; i<0x100; i++)
	{
		YM2151WriteReg(num, i, 0);
	}
}
