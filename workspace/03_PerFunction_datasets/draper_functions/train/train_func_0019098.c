slot_getallattrs(TupleTableSlot *slot)
{
	int			tdesc_natts = slot->tts_tupleDescriptor->natts;
	int			attnum;
	HeapTuple	tuple;


	if (slot->tts_nvalid == tdesc_natts)
		return;


	tuple = slot->tts_tuple;
	if (tuple == NULL)
		elog(ERROR, "cannot extract attribute from empty tuple slot");


	attnum = HeapTupleHeaderGetNatts(tuple->t_data);
	attnum = Min(attnum, tdesc_natts);

	slot_deform_tuple(slot, attnum);


	for (; attnum < tdesc_natts; attnum++)
	{
		slot->tts_values[attnum] = (Datum) 0;
		slot->tts_isnull[attnum] = true;
	}
	slot->tts_nvalid = tdesc_natts;
}
