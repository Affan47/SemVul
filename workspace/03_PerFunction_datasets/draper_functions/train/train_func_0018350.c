aosd_osd_check_composite_mgr ( void )
{


  int have_comp_mgr = ghosd_check_composite_mgr();

  if ( have_comp_mgr != 0 )
  {
    DEBUGMSG("running composite manager found\n");
    return have_comp_mgr;
  }
  else
  {


    gchar *soutput = NULL, *serror = NULL;
    gint exit_status;

    if ( g_spawn_command_line_sync( "ps -eo comm" ,
           &soutput , &serror , &exit_status , NULL ) == TRUE )
    {
      if (( soutput != NULL ) && ( strstr( soutput , "\nxcompmgr\n" ) != NULL ))
      {
        DEBUGMSG("running xcompmgr found\n");
        have_comp_mgr = 1;
      }
      else
      {
        DEBUGMSG("running xcompmgr not found\n");
        have_comp_mgr = 0;
      }
    }
    else
    {
      g_warning("command 'ps -eo comm' failed, unable to check if xcompgr is running\n");
      have_comp_mgr = 0;
    }

    g_free( soutput );
    g_free( serror );
    return have_comp_mgr;
  }
}
