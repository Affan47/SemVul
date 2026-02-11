RI_FKey_keyequal_upd_pk(Trigger *trigger, Relation pk_rel,
						HeapTuple old_row, HeapTuple new_row)
{
	int			tgnargs;
	char	  **tgargs;
	Relation	fk_rel;
	RI_QueryKey qkey;


	tgnargs = trigger->tgnargs;
	tgargs = trigger->tgargs;
	if (tgnargs < 4 ||
		tgnargs > RI_MAX_ARGUMENTS ||
		(tgnargs % 2) != 0)
		ereport(ERROR,
				(errcode(ERRCODE_E_R_I_E_TRIGGER_PROTOCOL_VIOLATED),
				 errmsg("function \"%s\" called with wrong number of trigger arguments",
						"RI_FKey_keyequal_upd")));


	if (tgnargs == 4)
		return true;

	if (!OidIsValid(trigger->tgconstrrelid))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
		   errmsg("no target table given for trigger \"%s\" on table \"%s\"",
				  trigger->tgname,
				  RelationGetRelationName(pk_rel)),
		  errhint("Remove this referential integrity trigger and its mates, "
				  "then do ALTER TABLE ADD CONSTRAINT.")));

	fk_rel = heap_open(trigger->tgconstrrelid, AccessShareLock);

	switch (ri_DetermineMatchType(tgargs[RI_MATCH_TYPE_ARGNO]))
	{
		case RI_MATCH_TYPE_UNSPECIFIED:
		case RI_MATCH_TYPE_FULL:
			ri_BuildQueryKeyFull(&qkey, trigger->tgoid,
								 RI_PLAN_KEYEQUAL_UPD,
								 fk_rel, pk_rel,
								 tgnargs, tgargs);
			heap_close(fk_rel, AccessShareLock);


			return ri_KeysEqual(pk_rel, old_row, new_row, &qkey,
								RI_KEYPAIR_PK_IDX);


		case RI_MATCH_TYPE_PARTIAL:
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("MATCH PARTIAL not yet implemented")));
			break;
	}


	elog(ERROR, "invalid match_type");
	return false;
}
