intf_get_dest_op_untyped ( struct interface *intf, void *type,
				  struct interface **dest ) {
	void *func;

	while ( 1 ) {


		func = intf_get_dest_op_no_passthru_untyped( intf, type, dest );
		if ( func )
			return func;


		if ( ! ( intf = intf_get_passthru ( *dest ) ) )
			return NULL;
		intf_put ( *dest );
	}
}
