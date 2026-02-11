DecimalYear () const
	{
	DBFloat decDate;
	DBInt month, day;

	decDate  = (FlagsVAR & DBTimeStepYear)  == DBTimeStepYear  ? Year () : 0.0;
	if ((FlagsVAR & DBTimeStepMonth) != DBTimeStepMonth) return (decDate + 0.5);
	if ((FlagsVAR & DBTimeStepDay)   != DBTimeStepDay)   return (decDate + ((DBFloat) Month () + 0.5) / 12.0);
	day = (DBDateIsLeapYear (Year ()) && (Month () > 1)) ? 1 : 0;
	for (month = 0;month < Month ();++month) day += _DBNumberOfDays [month];
	if ((FlagsVAR & DBTimeStepHour)  != DBTimeStepHour)
		return (decDate + (DBFloat) day / (DBDateIsLeapYear (Year ()) ? 365.0 : 366.0));
	if ((FlagsVAR & DBTimeStepMinute) != DBTimeStepMinute)
		return (decDate + ((DBFloat) day + Hour () / 24) / (DBDateIsLeapYear (Year ()) ? 365.0 : 366.0));
	return (decDate + ((DBFloat) day + (Hour () + Minute () / 60.0) / 24) / (DBDateIsLeapYear (Year ()) ? 365.0 : 366.0));
	}
