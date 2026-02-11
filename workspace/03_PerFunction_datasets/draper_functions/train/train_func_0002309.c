pokey_potgo(int chip)
{
	struct POKEYregisters *p = &pokey[chip];
    int pot;

	LOG(("POKEY #%d pokey_potgo\n", chip));

    p->ALLPOT = 0xff;

    for( pot = 0; pot < 8; pot++ )
	{
		p->POTx[pot] = 0xff;
		if( p->pot_r[pot] )
		{
			int r = (*p->pot_r[pot])(pot);
			LOG(("POKEY #%d pot_r(%d) returned $%02x\n", chip, pot, r));
			if( r != -1 )
			{
				if (r > 228)
                    r = 228;

                p->POTx[pot] = r;
				timer_adjust(p->ptimer[pot], TIME_IN_USEC(r * AD_TIME), (chip<<3)|pot, 0);
			}
		}
	}
}
