fill_gap(int ngaps, int ntsm[MAX_NTSM], int rangetsm[MAX_GAPS][2],
	     int vdatem[MAX_GAPS][MAX_NTSM], int vtimem[MAX_GAPS][MAX_NTSM],
	     int tsID, int incperiod0, int incunit0, int vdate, int vdate0, int vtime0,
	     int calendar, int day0, juldate_t juldate, juldate_t juldate0)
{
  int its = 0;
  int year, month, day;
  int ndate, ntime;
  int ijulinc = incperiod0 * iunits[incunit0];

  if ( ijulinc > 0 && ngaps < MAX_GAPS )
    {
      rangetsm[ngaps][0] = tsID;
      rangetsm[ngaps][1] = tsID+1;

      if ( incunit0 == TU_MONTHS || incunit0 == TU_YEARS )
	{
	  its = 0;
	  ndate = vdate0;

	  while ( TRUE )
	    {
	      cdiDecodeDate(ndate, &year, &month, &day);

	      month += ijulinc;

	      while ( month > 12 ) { month -= 12; year++; }
	      while ( month <  1 ) { month += 12; year--; }

	      if ( day0 == 31 )
		day = days_per_month(calendar, year, month);

	      ndate = cdiEncodeDate(year, month, day);
	      ntime = vtime0;
	      if ( ndate >= vdate ) break;

	      if ( its < MAX_NTSM )
		{
		  vdatem[ngaps][its] = ndate;
		  vtimem[ngaps][its] = ntime;
		}
	      else if ( its >= LIM_NTSM )
		break;

	      its++;
	    }
	}
      else
	{
	  its = 0;
	  juldate0 = juldate_add_seconds(ijulinc, juldate0);
	  while ( juldate_to_seconds(juldate0) < juldate_to_seconds(juldate) )
	    {
	      juldate_decode(calendar, juldate0, &ndate, &ntime);
	      juldate0 = juldate_add_seconds(ijulinc, juldate0);
	      if ( its < MAX_NTSM )
		{
		  vdatem[ngaps][its] = ndate;
		  vtimem[ngaps][its] = ntime;
		}
	      else if ( its >= LIM_NTSM )
		break;

	      its++;
	    }
	}
      ntsm[ngaps] = its;
    }

  return (its);
}
