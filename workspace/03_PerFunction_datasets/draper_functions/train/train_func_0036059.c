find_command(cmdchar)
    int		cmdchar;
{
    int		i;
    int		idx;
    int		top, bot;
    int		c;

#ifdef FEAT_MBYTE

    if (cmdchar >= 0x100)
	return -1;
#endif


    if (cmdchar < 0)
	cmdchar = -cmdchar;


    if (cmdchar <= nv_max_linear)
	return nv_cmd_idx[cmdchar];


    bot = nv_max_linear + 1;
    top = NV_CMDS_SIZE - 1;
    idx = -1;
    while (bot <= top)
    {
	i = (top + bot) / 2;
	c = nv_cmds[nv_cmd_idx[i]].cmd_char;
	if (c < 0)
	    c = -c;
	if (cmdchar == c)
	{
	    idx = nv_cmd_idx[i];
	    break;
	}
	if (cmdchar > c)
	    bot = i + 1;
	else
	    top = i - 1;
    }
    return idx;
}
