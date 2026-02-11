UDBIndex_allocPid(UDBIndex *self)
{
	PID_TYPE hole = (PID_TYPE)List_pop(self->holes);

	if (hole)
	{
		return hole;
	}
	else
	{
		PID_TYPE max = JFile_setPositionToEnd(self->file) / sizeof(UDBIndexEntry);

		if (max > self->maxPid)
		{
			self->maxPid = max;
		}
		else
		{
			self->maxPid ++;
		}

		return self->maxPid;
	}
}
