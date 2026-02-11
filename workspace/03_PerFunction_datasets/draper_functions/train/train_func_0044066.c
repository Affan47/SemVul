spgrescan(PG_FUNCTION_ARGS)
{
	IndexScanDesc scan = (IndexScanDesc) PG_GETARG_POINTER(0);
	SpGistScanOpaque so = (SpGistScanOpaque) scan->opaque;
	ScanKey		scankey = (ScanKey) PG_GETARG_POINTER(1);


	if (scankey && scan->numberOfKeys > 0)
	{
		memmove(scan->keyData, scankey,
				scan->numberOfKeys * sizeof(ScanKeyData));
	}


	spgPrepareScanKeys(scan);


	resetSpGistScanOpaque(so);

	PG_RETURN_VOID();
}
