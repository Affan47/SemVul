entry_to_tombstone ( Slapi_PBlock *pb, Slapi_Entry *entry )
{
	Slapi_Operation *op;
	Slapi_Mods smods;
	CSN *opcsn;
	const char *uniqueid;
	int op_result = LDAP_SUCCESS;

	slapi_pblock_get ( pb, SLAPI_OPERATION, &op );
	opcsn = operation_get_csn ( op );
	uniqueid = slapi_entry_get_uniqueid ( entry );


	slapi_mods_init ( &smods, 2 );

	slapi_mods_add ( &smods, LDAP_MOD_DELETE, SLAPI_ATTR_OBJECTCLASS, strlen("glue"), "glue");


	slapi_mods_add ( &smods, LDAP_MOD_DELETE, ATTR_NSDS5_REPLCONFLICT, 0, NULL );

	op_result = urp_fixup_modify_entry (uniqueid,
	                                    slapi_entry_get_sdn_const (entry),
	                                    opcsn, &smods, 0);
	slapi_mods_done ( &smods );


	if ( op_result == LDAP_SUCCESS )
	{


		op_result = urp_fixup_delete_entry (uniqueid, slapi_entry_get_dn_const (entry), opcsn, 0);
	}

	return op_result;
}
