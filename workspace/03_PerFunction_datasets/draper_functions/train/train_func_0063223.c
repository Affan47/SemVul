InitResultRelInfo(ResultRelInfo *resultRelInfo,
				  Relation resultRelationDesc,
				  Index resultRelationIndex,
				  CmdType operation,
				  int instrument_options)
{
	TriggerDesc	*trigDesc = resultRelationDesc->trigdesc;


	switch (resultRelationDesc->rd_rel->relkind)
	{
		case RELKIND_RELATION:

			break;
		case RELKIND_SEQUENCE:
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("cannot change sequence \"%s\"",
							RelationGetRelationName(resultRelationDesc))));
			break;
		case RELKIND_TOASTVALUE:
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("cannot change TOAST relation \"%s\"",
							RelationGetRelationName(resultRelationDesc))));
			break;
		case RELKIND_VIEW:
			switch (operation)
			{
				case CMD_INSERT:
					if (!trigDesc || !trigDesc->trig_insert_instead_row)
						ereport(ERROR,
								(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
								 errmsg("cannot insert into view \"%s\"",
										RelationGetRelationName(resultRelationDesc)),
								 errhint("You need an unconditional ON INSERT DO INSTEAD rule or an INSTEAD OF INSERT trigger.")));
					break;
				case CMD_UPDATE:
					if (!trigDesc || !trigDesc->trig_update_instead_row)
						ereport(ERROR,
								(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
								 errmsg("cannot update view \"%s\"",
										RelationGetRelationName(resultRelationDesc)),
								 errhint("You need an unconditional ON UPDATE DO INSTEAD rule or an INSTEAD OF UPDATE trigger.")));
					break;
				case CMD_DELETE:
					if (!trigDesc || !trigDesc->trig_delete_instead_row)
						ereport(ERROR,
								(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
								 errmsg("cannot delete from view \"%s\"",
										RelationGetRelationName(resultRelationDesc)),
								 errhint("You need an unconditional ON DELETE DO INSTEAD rule or an INSTEAD OF DELETE trigger.")));
					break;
				default:
					elog(ERROR, "unrecognized CmdType: %d", (int) operation);
					break;
			}
			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("cannot change relation \"%s\"",
							RelationGetRelationName(resultRelationDesc))));
			break;
	}


	MemSet(resultRelInfo, 0, sizeof(ResultRelInfo));
	resultRelInfo->type = T_ResultRelInfo;
	resultRelInfo->ri_RangeTableIndex = resultRelationIndex;
	resultRelInfo->ri_RelationDesc = resultRelationDesc;
	resultRelInfo->ri_NumIndices = 0;
	resultRelInfo->ri_IndexRelationDescs = NULL;
	resultRelInfo->ri_IndexRelationInfo = NULL;

	resultRelInfo->ri_TrigDesc = CopyTriggerDesc(trigDesc);
	if (resultRelInfo->ri_TrigDesc)
	{
		int			n = resultRelInfo->ri_TrigDesc->numtriggers;

		resultRelInfo->ri_TrigFunctions = (FmgrInfo *)
			palloc0(n * sizeof(FmgrInfo));
		resultRelInfo->ri_TrigWhenExprs = (List **)
			palloc0(n * sizeof(List *));
		if (instrument_options)
			resultRelInfo->ri_TrigInstrument = InstrAlloc(n, instrument_options);
	}
	else
	{
		resultRelInfo->ri_TrigFunctions = NULL;
		resultRelInfo->ri_TrigWhenExprs = NULL;
		resultRelInfo->ri_TrigInstrument = NULL;
	}
	resultRelInfo->ri_ConstraintExprs = NULL;
	resultRelInfo->ri_junkFilter = NULL;
	resultRelInfo->ri_projectReturning = NULL;


	if (resultRelationDesc->rd_rel->relhasindex &&
		operation != CMD_DELETE)
		ExecOpenIndices(resultRelInfo);
}
