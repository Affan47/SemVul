YM_DELTAT_synthesis_from_CPU_memory(YM_DELTAT *DELTAT)
{
	UINT32 step;
	int data;

	DELTAT->now_step += DELTAT->step;
	if ( DELTAT->now_step >= (1<<YM_DELTAT_SHIFT) )
	{
		step = DELTAT->now_step >> YM_DELTAT_SHIFT;
		DELTAT->now_step &= (1<<YM_DELTAT_SHIFT)-1;
		do{

			if( DELTAT->now_addr&1 )
			{
				data = DELTAT->now_data & 0x0f;

				DELTAT->now_data = DELTAT->CPU_data;


				if(DELTAT->status_set_handler)
					if(DELTAT->status_change_BRDY_bit)
						(DELTAT->status_set_handler)(DELTAT->status_change_which_chip, DELTAT->status_change_BRDY_bit);
			}
			else
			{
				data = DELTAT->now_data >> 4;
			}

			DELTAT->now_addr++;


			DELTAT->prev_acc = DELTAT->acc;


			DELTAT->acc += (ym_deltat_decode_tableB1[data] * DELTAT->adpcmd / 8);
			YM_DELTAT_Limit(DELTAT->acc,YM_DELTAT_DECODE_MAX, YM_DELTAT_DECODE_MIN);


			DELTAT->adpcmd = (DELTAT->adpcmd * ym_deltat_decode_tableB2[data] ) / 64;
			YM_DELTAT_Limit(DELTAT->adpcmd,YM_DELTAT_DELTA_MAX, YM_DELTAT_DELTA_MIN );


		}while(--step);

	}


	DELTAT->adpcml = DELTAT->prev_acc * (int)((1<<YM_DELTAT_SHIFT)-DELTAT->now_step);
	DELTAT->adpcml += (DELTAT->acc * (int)DELTAT->now_step);
	DELTAT->adpcml = (DELTAT->adpcml>>YM_DELTAT_SHIFT) * (int)DELTAT->volume;


	*(DELTAT->pan) += DELTAT->adpcml;
}
