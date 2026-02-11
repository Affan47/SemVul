ExecGetJunkAttribute(JunkFilter *junkfilter,
					 TupleTableSlot *slot,
					 char *attrName,
					 Datum *value,
					 bool *isNull)
{
	ListCell   *t;


	foreach(t, junkfilter->jf_targetList)
	{
		TargetEntry *tle = lfirst(t);

		if (tle->resjunk && tle->resname &&
			(strcmp(tle->resname, attrName) == 0))
		{

			*value = slot_getattr(slot, tle->resno, isNull);
			return true;
		}
	}


	return false;
}
