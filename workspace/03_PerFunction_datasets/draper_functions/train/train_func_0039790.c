init_stop(struct w *widgets)
{
    gchar *cmd;


    networkmanager_stop();


    cmd = g_strdup_printf("%s", SYSINIT_STOP_CMD);
    if( strlen(cmd) > 4 )
    {
	if( ! run_command(cmd) )
	{
	    run_command_show_err(cmd);

	}
    }
    g_free(cmd);


    cmd = g_strdup_printf("%s/gadmin-openvpn-client stop", SYSINIT_SCRIPTS_DIR);
    if( strlen(cmd) > 4 )
    {
	if( ! run_command(cmd) )
	{
	    run_command_show_err(cmd);
	}
    }
    g_free(cmd);
}
