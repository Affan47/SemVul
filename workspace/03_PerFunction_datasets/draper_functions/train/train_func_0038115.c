save_cmdline(ccp)
    struct cmdline_info *ccp;
{
    if (!prev_ccline_used)
    {
	vim_memset(&prev_ccline, 0, sizeof(struct cmdline_info));
	prev_ccline_used = TRUE;
    }
    *ccp = prev_ccline;
    prev_ccline = ccline;
    ccline.cmdbuff = NULL;
    ccline.cmdprompt = NULL;
    ccline.xpc = NULL;
}
