eval_map_expr(str)
    char_u	*str;
{
    char_u	*res;
    char_u	*p;
    char_u	*save_cmd;
    pos_T	save_cursor;

    save_cmd = save_cmdline_alloc();
    if (save_cmd == NULL)
	return NULL;


    ++textlock;
#ifdef FEAT_EX_EXTRA
    ++ex_normal_lock;
#endif
    save_cursor = curwin->w_cursor;
    p = eval_to_string(str, NULL, FALSE);
    --textlock;
#ifdef FEAT_EX_EXTRA
    --ex_normal_lock;
#endif
    curwin->w_cursor = save_cursor;

    restore_cmdline_alloc(save_cmd);
    if (p == NULL)
	return NULL;
    res = vim_strsave_escape_csi(p);
    vim_free(p);

    return res;
}
