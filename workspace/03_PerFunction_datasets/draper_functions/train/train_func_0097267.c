er_paf_get_matching_item
(struct er_paf_config * paf_configuration, const char * this_pro_catg)
    {
    struct er_paf_config_item * config_item = NULL;
    unsigned int                item;

    cpl_msg_indent_more();

    for(item = 0; item < paf_configuration->nitems; ++item)
	{
	regex_t pattern;
	int     regstatus;

	cpl_msg_debug(er_func, "Comparing PRO CATG with %s",
		paf_configuration->items[item].pro_catg_regexp);

	regstatus = regcomp(&pattern,
		paf_configuration->items[item].pro_catg_regexp,
		REG_EXTENDED|REG_NOSUB);
	if(regstatus)
	    {
	    cpl_msg_error(er_func, "Bad formatted PRO CATG regular expression");
	    cpl_error_set(er_func, CPL_ERROR_ILLEGAL_INPUT);
	    cpl_msg_indent_less();
	    regfree(&pattern);
	    return NULL;
	    }
	regstatus =
	    regexec(&pattern, this_pro_catg, (size_t)0, NULL, 0);
	if (regstatus != REG_NOMATCH)
	    {
	    config_item = paf_configuration->items+item;
	    cpl_msg_indent_less();
	    regfree(&pattern);
	    return config_item;
	    }
        regfree(&pattern);
	}
    cpl_msg_indent_less();


    return config_item;
    }
