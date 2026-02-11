locals_separator( char subj )
{
    bool retval = FALSE;

    if ( subj == '|' )
    {
	retval = TRUE;
	return ( retval );
    }

    if ( ibm_locals_legacy_separator )
    {
	if ( subj == ';' )
	{
	    retval = TRUE;
	    if ( ibm_legacy_separator_message )
	    {
		tokenization_error ( WARNING , "Semicolon as separator in "
		    "Locals declaration is deprecated in favor of '|'\n");
	    }
	}
    }
    return ( retval );
}
