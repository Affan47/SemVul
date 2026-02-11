gingetmulti(PG_FUNCTION_ARGS)
{
	IndexScanDesc scan = (IndexScanDesc) PG_GETARG_POINTER(0);
	ItemPointer tids = (ItemPointer) PG_GETARG_POINTER(1);
	int32		max_tids = PG_GETARG_INT32(2);
	int32	   *returned_tids = (int32 *) PG_GETARG_POINTER(3);

	if (GinIsNewKey(scan))
		newScanKey(scan);

	*returned_tids = 0;

	if (GinIsVoidRes(scan))
		PG_RETURN_BOOL(false);

	startScan(scan);

	do
	{
		if (scanGetItem(scan, tids + *returned_tids))
			(*returned_tids)++;
		else
			break;
	} while (*returned_tids < max_tids);

	PG_RETURN_BOOL(*returned_tids == max_tids);
}
