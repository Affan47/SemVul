stat_incl_list_file( char *base_name, struct stat *file_info)
{
    bool retval = FALSE;
    int stat_reslt = -1;

    init_incl_list_scan( base_name);
    while ( scan_incl_list( base_name) )
    {
        stat_reslt = stat( include_list_full_path, file_info);
	if ( stat_reslt == 0 )
	{
	    retval = TRUE;
	    break;
	}
    }

    return (retval);
}
