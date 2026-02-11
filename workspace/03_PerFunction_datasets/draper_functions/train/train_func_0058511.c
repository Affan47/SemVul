TourneySetTime (TOURNEYTIME ttime)
{
  int i, j;

  j = -1;
  for (i = 0; i < t_eventcount; i++)
    {
      if (t_eventlist[i].ttime == ttime && t_eventlist[i].taction == A_SET)
	{
	  j = t_eventlist[i].attime;
	  break;
	}
    }
  if (j <= 0)
    j = 71;
  return j;
}
