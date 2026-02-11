dgnc_set_custom_speed(struct channel_t *ch, uint newrate)
{
	int testdiv;
	int testrate_high;
	int testrate_low;
	int deltahigh;
	int deltalow;

	if (newrate <= 0) {
		ch->ch_custom_speed = 0;
		return;
	}


	if (newrate && newrate < ((ch->ch_bd->bd_dividend / 0xFFFF) + 1))
		newrate = ((ch->ch_bd->bd_dividend / 0xFFFF) + 1);

	if (newrate && newrate > ch->ch_bd->bd_dividend)
		newrate = ch->ch_bd->bd_dividend;

	if (newrate > 0) {
		testdiv = ch->ch_bd->bd_dividend / newrate;


		testrate_high = ch->ch_bd->bd_dividend / testdiv;
		testrate_low  = ch->ch_bd->bd_dividend / (testdiv + 1);


		if (testrate_high != newrate) {


			deltahigh = testrate_high - newrate;
			deltalow = newrate - testrate_low;

			if (deltahigh < deltalow)
				newrate = testrate_high;
			else
				newrate = testrate_low;
		}
	}

	ch->ch_custom_speed = newrate;
}
