init_stop(struct w *widgets)
{
    gchar *cmd;


    cmd = g_strdup_printf("%s", SYSINIT_STOP_CMD);
    if( strlen(cmd) > 4 )
    {
	if( ! run_command(cmd) )
	{
	    run_command_show_err(cmd);
	}
    }
    if( cmd!=NULL )
      g_free(cmd);


    cmd = g_strdup_printf("%s/gadmin-openvpn-server stop", SYSINIT_SCRIPTS_DIR);
    if( strlen(cmd) > 4 )
    {
	if( ! run_command(cmd) )
	{
	    run_command_show_err(cmd);
	}
    }
    if( cmd!=NULL )
      g_free(cmd);
}
