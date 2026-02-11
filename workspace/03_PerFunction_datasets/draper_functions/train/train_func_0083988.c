entry_assign_operation_csn ( Slapi_PBlock *pb, Slapi_Entry *e, Slapi_Entry *parententry )
{
	Slapi_Operation *op;
	const CSN *basecsn = NULL;
	const CSN *parententry_dncsn = NULL;
	CSN *opcsn = NULL;

	slapi_pblock_get ( pb, SLAPI_OPERATION, &op );


	if ( op->o_csngen_handler )
	{


		if ( e )
		{
			basecsn = entry_get_maxcsn ( e );
		}
		if ( parententry )
		{
			parententry_dncsn = entry_get_dncsn ( parententry );
			if ( csn_compare ( parententry_dncsn, basecsn ) > 0 )
			{
				basecsn = parententry_dncsn;
			}
		}
		opcsn = op->o_csngen_handler ( pb, basecsn );

		if (NULL != opcsn)
		{
			operation_set_csn (op, opcsn);
		}
	}

	return opcsn;
}
