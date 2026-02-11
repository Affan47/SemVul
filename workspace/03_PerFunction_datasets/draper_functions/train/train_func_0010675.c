phrase(struct gdstate *gds)
{
	if (timephrase(gds))
		return 1;
	if (zonephrase(gds))
		return 1;
	if (datephrase(gds))
		return 1;
	if (dayphrase(gds))
		return 1;
	if (relunitphrase(gds)) {
		if (gds->tokenp[0].token == tAGO) {
			gds->RelSeconds = -gds->RelSeconds;
			gds->RelMonth = -gds->RelMonth;
			gds->tokenp += 1;
		}
		return 1;
	}


	if (gds->tokenp[0].token == tUNUMBER) {
		if (gds->HaveTime && !gds->HaveYear && !gds->HaveRel) {
			gds->HaveYear++;
			gds->Year = gds->tokenp[0].value;
			gds->tokenp += 1;
			return 1;
		}

		if(gds->tokenp[0].value > 10000) {

			gds->HaveYear++;
			gds->HaveMonth++;
			gds->HaveDay++;
			gds->Day= (gds->tokenp[0].value)%100;
			gds->Month= (gds->tokenp[0].value/100)%100;
			gds->Year = gds->tokenp[0].value/10000;
			gds->tokenp += 1;
			return 1;
		}

		if (gds->tokenp[0].value < 24) {
			gds->HaveTime++;
			gds->Hour = gds->tokenp[0].value;
			gds->Minutes = 0;
			gds->Seconds = 0;
			gds->tokenp += 1;
			return 1;
		}

		if ((gds->tokenp[0].value / 100 < 24)
		    && (gds->tokenp[0].value % 100 < 60)) {

			gds->Hour = gds->tokenp[0].value / 100;
			gds->Minutes = gds->tokenp[0].value % 100;
			gds->Seconds = 0;
			gds->tokenp += 1;
			return 1;
		}
	}

	return 0;
}
