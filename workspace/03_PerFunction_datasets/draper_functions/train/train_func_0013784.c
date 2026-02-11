ins_compl_add_tv(tv, dir)
    typval_T	*tv;
    int		dir;
{
    char_u	*word;
    int		icase = FALSE;
    int		adup = FALSE;
    int		aempty = FALSE;
    char_u	*(cptext[CPT_COUNT]);

    if (tv->v_type == VAR_DICT && tv->vval.v_dict != NULL)
    {
	word = get_dict_string(tv->vval.v_dict, (char_u *)"word", FALSE);
	cptext[CPT_ABBR] = get_dict_string(tv->vval.v_dict,
						     (char_u *)"abbr", FALSE);
	cptext[CPT_MENU] = get_dict_string(tv->vval.v_dict,
						     (char_u *)"menu", FALSE);
	cptext[CPT_KIND] = get_dict_string(tv->vval.v_dict,
						     (char_u *)"kind", FALSE);
	cptext[CPT_INFO] = get_dict_string(tv->vval.v_dict,
						     (char_u *)"info", FALSE);
	if (get_dict_string(tv->vval.v_dict, (char_u *)"icase", FALSE) != NULL)
	    icase = get_dict_number(tv->vval.v_dict, (char_u *)"icase");
	if (get_dict_string(tv->vval.v_dict, (char_u *)"dup", FALSE) != NULL)
	    adup = get_dict_number(tv->vval.v_dict, (char_u *)"dup");
	if (get_dict_string(tv->vval.v_dict, (char_u *)"empty", FALSE) != NULL)
	    aempty = get_dict_number(tv->vval.v_dict, (char_u *)"empty");
    }
    else
    {
	word = get_tv_string_chk(tv);
	vim_memset(cptext, 0, sizeof(cptext));
    }
    if (word == NULL || (!aempty && *word == NUL))
	return FAIL;
    return ins_compl_add(word, -1, icase, NULL, cptext, dir, 0, adup);
}
