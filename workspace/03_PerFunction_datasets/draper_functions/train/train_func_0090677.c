get_gadmin_samba_users()
{
    gchar *cmd;


    cmd = g_strdup_printf("touch %s && chmod 600 %s\n", GADMIN_SAMBA_USERS, GADMIN_SAMBA_USERS);
    if( ! run_command(cmd) )
    {
	printf("Show info here: Creating an initial gadmin_samba_users file failed.\n");
    }
    g_free(cmd);


    cmd = g_strdup_printf("%s -L -w > %s\n", PDBEDIT_BINARY, GADMIN_SAMBA_USERS);
    if( ! run_command(cmd) )
    {
	printf("Show info here: pbedit -L -w -v failed.\n");
    }
    g_free(cmd);
}
