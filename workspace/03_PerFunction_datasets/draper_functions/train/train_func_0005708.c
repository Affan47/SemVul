time_denytime_check(time_t t, struct denytime *dt)
{
int		reverse, sm,em,cm;
struct	tm	tm;
char		todaybit, dmask,yestdbit;

    if ( !dt ) return(0);

    localtime_r(&t, &tm);
    cm = tm.tm_hour * 60 + tm.tm_min;
    todaybit = 1 << tm.tm_wday;

    while(dt) {

	sm = dt->start_minute;
	em = dt->end_minute;
	dmask = dt->days;


	if ( sm < em ) reverse = FALSE;
	   else	       reverse = TRUE;

	if ( !reverse ) {

	    if ( TEST(todaybit, dmask) ) {

		if ( sm <= cm && cm <= em )
			return(1);
		  else
			goto check_next_dt;
	    } else
		goto check_next_dt;
	} else {

	    if ( TEST(todaybit, dmask) ) {
		if ( cm >= sm )
		    return(1);
		yestdbit = todaybit >> 1;

		if ( !yestdbit ) yestdbit = 0x40;

		if ( !TEST(yestdbit, dmask) )
		    goto check_next_dt;

		if ( cm <= em )
		    return(1);

		goto check_next_dt;
	    }
	}

 check_next_dt:;
	dt = dt->next;
    }
    return(0);
}
