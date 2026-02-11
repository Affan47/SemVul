option_get_command(dstr_t *cmd, option_t *opt, int optionset, int section)
{
    const char *valstr;
    choice_t *choice = NULL;

    dstrclear(cmd);

    if (option_is_composite(opt))
        return composite_get_command(cmd, opt, optionset, section);

    if (section >= 0 && !option_is_in_section(opt, section))
        return 1;

    valstr = option_get_value(opt, optionset);
    if (!valstr)
        return 0;


    choice = option_find_choice(opt, valstr);
    if (choice && (*choice->command ||
		   ((opt->type != TYPE_INT) && (opt->type != TYPE_FLOAT)))) {
        dstrcpy(cmd, choice->command);
        return 1;
    }


    if ((opt->type == TYPE_STRING || opt->type == TYPE_PASSWORD) &&
	!strcasecmp(valstr, "None"))
        valstr = "";


    if (option_use_foomatic_prototype(opt))
	build_foomatic_custom_command(cmd, opt, valstr);
    else {
	dstrcpy(cmd, opt->custom_command);
	if ((option_get_section(opt) == SECTION_JCLSETUP) ||
	    (opt->style == 'J'))
	    build_cups_custom_jcl_command(cmd, opt, valstr);
	else
	  build_cups_custom_ps_command(cmd, opt, valstr);
    }

    return cmd->len != 0;
}
