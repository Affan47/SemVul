find_var_in_ht(ht, varname, writing)
    hashtab_T	*ht;
    char_u	*varname;
    int		writing;
{
    hashitem_T	*hi;

    if (*varname == NUL)
    {

	switch (varname[-2])
	{
	    case 's': return &SCRIPT_SV(current_SID)->sv_var;
	    case 'g': return &globvars_var;
	    case 'v': return &vimvars_var;
	    case 'b': return &curbuf->b_bufvar;
	    case 'w': return &curwin->w_winvar;
#ifdef FEAT_WINDOWS
	    case 't': return &curtab->tp_winvar;
#endif
	    case 'l': return current_funccal == NULL
					? NULL : &current_funccal->l_vars_var;
	    case 'a': return current_funccal == NULL
				       ? NULL : &current_funccal->l_avars_var;
	}
	return NULL;
    }

    hi = hash_find(ht, varname);
    if (HASHITEM_EMPTY(hi))
    {


	if (ht == &globvarht && !writing)
	{


	    if (!script_autoload(varname, FALSE) || aborting())
		return NULL;
	    hi = hash_find(ht, varname);
	}
	if (HASHITEM_EMPTY(hi))
	    return NULL;
    }
    return HI2DI(hi);
}
