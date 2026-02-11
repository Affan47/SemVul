syn_add_group(name)
    char_u	*name;
{
    char_u	*p;


    for (p = name; *p != NUL; ++p)
    {
	if (!vim_isprintc(*p))
	{
	    EMSG(_("E669: Unprintable character in group name"));
	    vim_free(name);
	    return 0;
	}
	else if (!ASCII_ISALNUM(*p) && *p != '_')
	{


	    msg_source(hl_attr(HLF_W));
	    MSG(_("W18: Invalid character in group name"));
	    break;
	}
    }


    if (highlight_ga.ga_data == NULL)
    {
	highlight_ga.ga_itemsize = sizeof(struct hl_group);
	highlight_ga.ga_growsize = 10;
    }

    if (highlight_ga.ga_len >= MAX_HL_ID)
    {
	EMSG(_("E849: Too many highlight and syntax groups"));
	vim_free(name);
	return 0;
    }


    if (ga_grow(&highlight_ga, 1) == FAIL)
    {
	vim_free(name);
	return 0;
    }

    vim_memset(&(HL_TABLE()[highlight_ga.ga_len]), 0, sizeof(struct hl_group));
    HL_TABLE()[highlight_ga.ga_len].sg_name = name;
    HL_TABLE()[highlight_ga.ga_len].sg_name_u = vim_strsave_up(name);
#ifdef FEAT_GUI
    HL_TABLE()[highlight_ga.ga_len].sg_gui_bg = INVALCOLOR;
    HL_TABLE()[highlight_ga.ga_len].sg_gui_fg = INVALCOLOR;
    HL_TABLE()[highlight_ga.ga_len].sg_gui_sp = INVALCOLOR;
#endif
    ++highlight_ga.ga_len;

    return highlight_ga.ga_len;
}
