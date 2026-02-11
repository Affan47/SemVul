urp_fixup_add_entry (Slapi_Entry *e, const char *target_uniqueid, const char *parentuniqueid, CSN *opcsn, int opflags)
{
	Slapi_PBlock *newpb;
	Slapi_Operation *op;
	int op_result;

	newpb = slapi_pblock_new ();


	slapi_add_entry_internal_set_pb (
			newpb,
			e,
			NULL,
			repl_get_plugin_identity ( PLUGIN_MULTIMASTER_REPLICATION ),
			OP_FLAG_REPLICATED | OP_FLAG_REPL_FIXUP | opflags);
	if (target_uniqueid)
	{
		slapi_pblock_set( newpb, SLAPI_TARGET_UNIQUEID, (void*)target_uniqueid);
	}
	if (parentuniqueid)
	{
		struct slapi_operation_parameters *op_params;
		slapi_pblock_get( newpb, SLAPI_OPERATION_PARAMETERS, &op_params );
		op_params->p.p_add.parentuniqueid = (char*)parentuniqueid;
	}
	slapi_pblock_get ( newpb, SLAPI_OPERATION, &op );
	operation_set_csn ( op, opcsn );

	slapi_add_internal_pb ( newpb );
	slapi_pblock_get ( newpb, SLAPI_PLUGIN_INTOP_RESULT, &op_result );
	slapi_pblock_destroy ( newpb );

	return op_result;
}
