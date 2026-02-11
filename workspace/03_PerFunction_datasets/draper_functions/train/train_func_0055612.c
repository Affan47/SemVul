resume_device_scope( void )
{
    if ( scope_is_global )
    {
	tokenization_error( INFO,
	    "Terminating Global Scope definitions; "
		"resuming Device-node definitions.\n" );
	current_definitions = save_device_definitions;
	scope_is_global = FALSE;
    }else{
	tokenization_error( WARNING,
	    "%s -- Device-node Scope already in effect; ignoring.\n",
		strupr(statbuf) );
    }

}
