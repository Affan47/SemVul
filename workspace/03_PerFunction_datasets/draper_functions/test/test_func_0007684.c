ds_bring_up_server(int verbose)
{
    char     *instdir;
    int      status;
    char     *errorlog;
    status = ds_get_updown_status();
    if ( status == DS_SERVER_UP )
        return(DS_SERVER_ALREADY_UP);
    if ( (instdir = ds_get_instance_dir()) == NULL )
        return(DS_SERVER_UNKNOWN);

    errorlog = ds_get_config_value(DS_ERRORLOG);
    if ( errorlog == NULL ) {
      errorlog = ds_get_errors_name();
    }
   return ds_bring_up_server_install(verbose, instdir, errorlog);
}
