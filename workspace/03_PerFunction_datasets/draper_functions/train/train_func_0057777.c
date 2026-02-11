assign_transaction_read_only(bool newval, bool doit, GucSource source)
{

	if (newval == false && XactReadOnly && IsSubTransaction())
	{
		ereport(GUC_complaint_elevel(source),
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("cannot set transaction read-write mode inside a read-only transaction")));

		if (source != PGC_S_OVERRIDE)
			return false;
	}
	return true;
}
