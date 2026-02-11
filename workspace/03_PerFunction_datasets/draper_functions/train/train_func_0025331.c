time_to_elap_short(time_t dur, char *elap)
{
	int days=0,hrs=0,mins=0,secs=0;

	elap[0] = 0;

	days = (int)(dur / 86400);
	dur -= (int)(dur / 86400) * 86400;

	hrs = (int)(dur / 3600);
	dur -= (int)(dur / 3600) * 3600;

	mins = (int)(dur / 60);
	secs = dur - (int)(dur / 60) * 60;

	if(days)
		sprintf(elap,"%dd",days);
	else if(hrs)
		sprintf(elap,"%dh",hrs);
	else if(mins)
		sprintf(elap,"%dm",mins);
	else
		sprintf(elap,"%ds",secs);
}
