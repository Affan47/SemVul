tokenization_error( int err_type, char* msg, ... )
{
    int indx ;


    char *catgy_name = "Error";
    char *catgy_suffx = "";
    int *catgy_counter = &err_count;
    bool print_new_line = FALSE;


    err_types_found |= err_type;


    for ( indx = 0 ; indx < num_categories ; indx ++ )
    {
        if ( ( error_categories[indx].type_bit & err_type ) != 0 )
        {
            catgy_name = error_categories[indx].category_name;
            catgy_suffx = error_categories[indx].single;
            catgy_counter = error_categories[indx].counter;
	    print_new_line = error_categories[indx].new_line;
            break;
        }
    }


    if ( catgy_name == NULL )
    {
         fprintf(ERRMSG_DESTINATION,
	      "Program error: Unknown Error-Type, 0x%08x.  "
              "  Will treat as Error.\n", err_type) ;
         err_types_found |= TKERROR;
         print_msg = TRUE ;
    } else {

         print_msg = BOOLVAL( ( errs_to_print & err_type ) != 0 );
    }

    if ( print_msg )
    {
        va_list argp;

	fprintf(ERRMSG_DESTINATION, "%s%s:  ",
             catgy_name, catgy_suffx);
        if ( iname != NULL )
	{

	    fprintf(ERRMSG_DESTINATION, "File %s, Line %d.  ",
        	 iname, lineno);
	}
        if ( opc > 0 )
	{

	    fprintf(ERRMSG_DESTINATION, "(Output Position = %d).  ", opc);
	}
        if ( pci_hdr_end_ob_off > 0 )
	{

	    fprintf(ERRMSG_DESTINATION, "(PCI-Block Position = %d).  ",
	        opc - pci_hdr_end_ob_off );
	}

        va_start(argp, msg);
        vfprintf(ERRMSG_DESTINATION, msg, argp);
        va_end(argp);
	if ( print_new_line ) fprintf(ERRMSG_DESTINATION, "\n");


	*catgy_counter += 1;
    }
    if ( err_type == FATAL )
    {
        fprintf(ERRMSG_DESTINATION, "Tokenization terminating.\n");
        error_summary();
        exit ( fatal_err_exit );
    }
}
