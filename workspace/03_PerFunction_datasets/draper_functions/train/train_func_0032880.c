UDB_at_(UDB *self, PID_TYPE pid)
{
	Datum d;
	UDBRecord *record = UDB_recordAtPid_(self, pid);

	if (!record)
	{
		d.size = 0;
		d.data = NULL;

		return d;
	}

	return UDBRecord_readDatum(record);
}
