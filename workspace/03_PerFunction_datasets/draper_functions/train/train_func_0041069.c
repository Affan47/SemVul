ExecScanReScan(ScanState *node)
{
	EState	   *estate = node->ps.state;


	node->ps.ps_TupFromTlist = false;


	if (estate->es_epqScanDone != NULL)
	{
		Index		scanrelid = ((Scan *) node->ps.plan)->scanrelid;

		Assert(scanrelid > 0);

		estate->es_epqScanDone[scanrelid - 1] = false;
	}
}
