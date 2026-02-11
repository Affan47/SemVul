currentDate(void)
{
  static MSBoolean firstTime=MSTrue;
  static MSJulian override=0;
  static MSBoolean useOverride=MSFalse;

  if (firstTime==MSTrue)
    {
      firstTime=MSFalse;
      char *cp=getenv("TB_DATE_OVERRIDE");
      if (cp)
	{
	  MSMBSDate d;
	  if (d.set(cp)==MSError::MSSuccess)
	    {
	      override=d._date;
	      useOverride=MSTrue;
	    }
	  else
	    {
	      MSMessageLog::errorMessage("MSMBSDate: TB_DATE_OVERRIDE contains an invalid date\n");
	      MSMessageLog::errorMessage("MSMBSDate: ignoring attempt to override\n");
	      useOverride=MSFalse;
	    }
	}
      else
	{
	  useOverride=MSFalse;
	}
    }

  if (useOverride==MSTrue)
    {
      return override;
    }
  else
    {
      #ifdef MS_THREAD_SAFE_FUNCTIONS
      struct tm tms;
      #endif

      time_t clk=time(0);
      struct tm *now=MS_LOCALTIME(&clk,&tms);
      return as30_360(now->tm_mon+1,now->tm_mday,now->tm_year+1900);
    }
}
