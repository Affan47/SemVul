operator< (DBDate date0,DBDate date1)

	{
	DBInt year0, year1;

	year0 = (date0.FlagsVAR &  DBTimeStepYear) == DBTimeStepYear ? date0.Year () :
			 ((date1.FlagsVAR &  DBTimeStepYear) == DBTimeStepYear ? date1.Year () : DBFault);
	year1 = (date1.FlagsVAR &  DBTimeStepYear) == DBTimeStepYear ? date1.Year () :
			 ((date0.FlagsVAR &  DBTimeStepYear) == DBTimeStepYear ? date0.Year () : DBFault);
	if (year0 < year1) return (true);
	if (year0 > year1) return (false);

	if ((date0.FlagsVAR &  DBTimeStepMonth)	!= DBTimeStepMonth)		return (false);
	if	((date1.FlagsVAR &  DBTimeStepMonth)	!= DBTimeStepMonth)		return (false);
	if (date0.Month () < date1.Month ())	return (true);
	if (date0.Month () > date1.Month ())	return (false);
	if ((date0.FlagsVAR &  DBTimeStepDay)		!= DBTimeStepDay)			return (false);
	if ((date1.FlagsVAR &  DBTimeStepDay)		!= DBTimeStepDay)			return (false);
	if (date0.Day () < date1.Day ())			return (true);
	if (date0.Day () > date1.Day ())			return (false);
	if ((date0.FlagsVAR &  DBTimeStepHour)		!= DBTimeStepHour)		return (false);
	if	((date1.FlagsVAR &  DBTimeStepHour)		!= DBTimeStepHour)		return (false);
	if (date0.Hour () < date1.Hour ())		return (true);
	if (date0.Hour () > date1.Hour ())		return (false);
	if ((date0.FlagsVAR &  DBTimeStepMinute)	!= DBTimeStepMinute)		return (false);
	if ((date1.FlagsVAR &  DBTimeStepMinute)	!= DBTimeStepMinute)		return (false);
	if (date0.Minute () < date1.Minute ()) return (true);
	return (false);
	}
