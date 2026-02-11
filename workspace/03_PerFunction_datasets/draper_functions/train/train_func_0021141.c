tv_equal(tv1, tv2, ic, recursive)
    typval_T *tv1;
    typval_T *tv2;
    int	     ic;
    int	     recursive;
{
    char_u	buf1[NUMBUFLEN], buf2[NUMBUFLEN];
    char_u	*s1, *s2;
    static int  recursive_cnt = 0;
    int		r;

    if (tv1->v_type != tv2->v_type)
	return FALSE;


    if (!recursive)
	tv_equal_recurse_limit = 1000;
    if (recursive_cnt >= tv_equal_recurse_limit)
    {
	--tv_equal_recurse_limit;
	return TRUE;
    }

    switch (tv1->v_type)
    {
	case VAR_LIST:
	    ++recursive_cnt;
	    r = list_equal(tv1->vval.v_list, tv2->vval.v_list, ic, TRUE);
	    --recursive_cnt;
	    return r;

	case VAR_DICT:
	    ++recursive_cnt;
	    r = dict_equal(tv1->vval.v_dict, tv2->vval.v_dict, ic, TRUE);
	    --recursive_cnt;
	    return r;

	case VAR_FUNC:
	    return (tv1->vval.v_string != NULL
		    && tv2->vval.v_string != NULL
		    && STRCMP(tv1->vval.v_string, tv2->vval.v_string) == 0);

	case VAR_NUMBER:
	    return tv1->vval.v_number == tv2->vval.v_number;

#ifdef FEAT_FLOAT
	case VAR_FLOAT:
	    return tv1->vval.v_float == tv2->vval.v_float;
#endif

	case VAR_STRING:
	    s1 = get_tv_string_buf(tv1, buf1);
	    s2 = get_tv_string_buf(tv2, buf2);
	    return ((ic ? MB_STRICMP(s1, s2) : STRCMP(s1, s2)) == 0);
    }

    EMSG2(_(e_intern2), "tv_equal()");
    return TRUE;
}
