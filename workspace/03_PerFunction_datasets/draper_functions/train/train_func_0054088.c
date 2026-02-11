rescanLatestTimeLine(void)
{
	TimeLineID	newtarget;

	newtarget = findNewestTimeLine(recoveryTargetTLI);
	if (newtarget != recoveryTargetTLI)
	{


		List	   *newExpectedTLIs;

		newExpectedTLIs = readTimeLineHistory(newtarget);


		if (!list_member_int(newExpectedTLIs,
							 (int) recoveryTargetTLI))
			ereport(LOG,
					(errmsg("new timeline %u is not a child of database system timeline %u",
							newtarget,
							ThisTimeLineID)));
		else
		{

			recoveryTargetTLI = newtarget;
			list_free(expectedTLIs);
			expectedTLIs = newExpectedTLIs;

			XLogCtl->RecoveryTargetTLI = recoveryTargetTLI;

			ereport(LOG,
					(errmsg("new target timeline is %u",
							recoveryTargetTLI)));
			return true;
		}
	}
	return false;
}
