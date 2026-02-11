sl_loop(SL_cmd *cmds, const char *prompt)
{
    void *data = NULL;
    int ret;
    while((ret = sl_command_loop(cmds, prompt, &data)) >= 0)
	;
    return ret;
}
