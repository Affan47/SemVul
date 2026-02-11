sl_apropos (SL_cmd *cmd, const char *topic)
{
    for (; cmd->name != NULL; ++cmd)
        if (cmd->usage != NULL && strstr(cmd->usage, topic) != NULL)
	    printf ("%-20s%s\n", cmd->name, cmd->usage);
}
