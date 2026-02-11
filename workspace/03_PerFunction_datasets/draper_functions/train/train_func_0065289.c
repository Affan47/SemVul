extended_op_oid2string( const char *oid )
{
	const char *rval = NULL;

	if ( 0 == strcmp(oid, EXTOP_BULK_IMPORT_START_OID)) {
		rval = "Bulk Import Start";
	} else if ( 0 == strcmp(oid, EXTOP_BULK_IMPORT_DONE_OID)) {
		rval = "Bulk Import End";
	} else {
		rval = plugin_extended_op_oid2string( oid );
	}

	return( rval );
}
