validateForeignKeyConstraint(char *conname,
							 Relation rel,
							 Relation pkrel,
							 Oid pkindOid,
							 Oid constraintOid)
{
	HeapScanDesc scan;
	HeapTuple	tuple;
	Trigger		trig;
	Snapshot	snapshot;

	ereport(DEBUG1,
			(errmsg("validating foreign key constraint \"%s\"", conname)));


	MemSet(&trig, 0, sizeof(trig));
	trig.tgoid = InvalidOid;
	trig.tgname = conname;
	trig.tgenabled = TRIGGER_FIRES_ON_ORIGIN;
	trig.tgisinternal = TRUE;
	trig.tgconstrrelid = RelationGetRelid(pkrel);
	trig.tgconstrindid = pkindOid;
	trig.tgconstraint = constraintOid;
	trig.tgdeferrable = FALSE;
	trig.tginitdeferred = FALSE;


	if (RI_Initial_Check(&trig, rel, pkrel))
		return;


	snapshot = RegisterSnapshot(GetLatestSnapshot());
	scan = heap_beginscan(rel, snapshot, 0, NULL);

	while ((tuple = heap_getnext(scan, ForwardScanDirection)) != NULL)
	{
		FunctionCallInfoData fcinfo;
		TriggerData trigdata;


		MemSet(&fcinfo, 0, sizeof(fcinfo));


		trigdata.type = T_TriggerData;
		trigdata.tg_event = TRIGGER_EVENT_INSERT | TRIGGER_EVENT_ROW;
		trigdata.tg_relation = rel;
		trigdata.tg_trigtuple = tuple;
		trigdata.tg_newtuple = NULL;
		trigdata.tg_trigger = &trig;
		trigdata.tg_trigtuplebuf = scan->rs_cbuf;
		trigdata.tg_newtuplebuf = InvalidBuffer;

		fcinfo.context = (Node *) &trigdata;

		RI_FKey_check_ins(&fcinfo);
	}

	heap_endscan(scan);
	UnregisterSnapshot(snapshot);
}
