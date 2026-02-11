set_cl_flag(char *flag_name, bool from_src)
{
    bool retval = TRUE;

    was_upper_case_tk = upper_case_tokens;
    was_lower_case_tk = lower_case_tokens;

    if ( strlen(flag_name) > 3 )
    {
	int indx;
	bool flagval = TRUE;
	char *compar = flag_name;

	if ( strncasecmp( flag_name, "no", 2) == 0 )
	{
	    flagval = FALSE;
	    compar += 2;
	}
	for ( indx = 0 ; indx < number_of_cl_flags ; indx++ )
	{
	    if ( strcasecmp( compar, cl_flags_list[indx].clflag_name ) == 0 )
	    {
		retval = FALSE;
		*(cl_flags_list[indx].flag_var) = flagval;


		if ( indx != number_of_cl_flags - 1 )
		{
		    cl_flag_change = TRUE;
		}
		if ( from_src )
		{
		    tokenization_error(INFO,
		    "%sabling:  %s\n",
		    flagval ? "En" : "Dis", cl_flags_list[indx].clflag_expln);
		}
		break;
	    }
	}
    }

    if ( retval )
    {
       const char* msg_txt = "Unknown Special-Feature Flag:  %s\n" ;
       if ( from_src )
       {
           tokenization_error( TKERROR, (char *)msg_txt, flag_name);
       }else{
	   if ( first_err_msg )
	   {
	       printf( "\n");
	       first_err_msg = FALSE;
	   }
	   printf( msg_txt, flag_name);
       }
    }

    adjust_case_flags();

    return ( retval );
}
