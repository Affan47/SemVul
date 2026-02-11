YM3812UpdateOne(int which, INT16 *buffer, int length)
{
	FM_OPL		*OPL = OPL_YM3812[which];
	UINT8		rhythm = OPL->rhythm&0x20;
	OPLSAMPLE	*buf = buffer;
	int i;

	if( (void *)OPL != cur_chip ){
		cur_chip = (void *)OPL;

		SLOT7_1 = &OPL->P_CH[7].SLOT[SLOT1];
		SLOT7_2 = &OPL->P_CH[7].SLOT[SLOT2];
		SLOT8_1 = &OPL->P_CH[8].SLOT[SLOT1];
		SLOT8_2 = &OPL->P_CH[8].SLOT[SLOT2];
	}
	for( i=0; i < length ; i++ )
	{
		int lt;

		output[0] = 0;

		advance_lfo(OPL);


		OPL_CALC_CH(&OPL->P_CH[0]);
		OPL_CALC_CH(&OPL->P_CH[1]);
		OPL_CALC_CH(&OPL->P_CH[2]);
		OPL_CALC_CH(&OPL->P_CH[3]);
		OPL_CALC_CH(&OPL->P_CH[4]);
		OPL_CALC_CH(&OPL->P_CH[5]);

		if(!rhythm)
		{
			OPL_CALC_CH(&OPL->P_CH[6]);
			OPL_CALC_CH(&OPL->P_CH[7]);
			OPL_CALC_CH(&OPL->P_CH[8]);
		}
		else
		{
			OPL_CALC_RH(&OPL->P_CH[0], (OPL->noise_rng>>0)&1 );
		}

		lt = output[0];

		lt >>= FINAL_SH;

      MAME_CLAMP_SAMPLE(lt);

		#ifdef SAVE_SAMPLE
		if (which==0)
		{
			SAVE_ALL_CHANNELS
		}
		#endif


		buf[i] = lt;

		advance(OPL);
	}

}
