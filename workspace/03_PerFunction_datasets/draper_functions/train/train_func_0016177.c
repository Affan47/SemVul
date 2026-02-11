do_swapexists(buf, fname)
    buf_T	*buf;
    char_u	*fname;
{
    set_vim_var_string(VV_SWAPNAME, fname, -1);
    set_vim_var_string(VV_SWAPCHOICE, NULL, -1);


    ++allbuf_lock;
    apply_autocmds(EVENT_SWAPEXISTS, buf->b_fname, NULL, FALSE, NULL);
    --allbuf_lock;

    set_vim_var_string(VV_SWAPNAME, NULL, -1);

    switch (*get_vim_var_str(VV_SWAPCHOICE))
    {
	case 'o': return 1;
	case 'e': return 2;
	case 'r': return 3;
	case 'd': return 4;
	case 'q': return 5;
	case 'a': return 6;
    }

    return 0;
}
