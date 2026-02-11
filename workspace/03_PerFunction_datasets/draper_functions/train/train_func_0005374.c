MFDateSetCurrent (char *currentDate) {
	if (_MFDateSet (&_MFCurrentDate,currentDate))
		return (_MFDateCompare (&_MFStartDate,&_MFCurrentDate) < 0 ? MFDateSetStart (currentDate): true);
	return (false);
}
