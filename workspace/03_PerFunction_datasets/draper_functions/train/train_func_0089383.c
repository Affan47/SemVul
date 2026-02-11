f_iconv(argvars, rettv)
    typval_T	*argvars UNUSED;
    typval_T	*rettv;
{
#ifdef FEAT_MBYTE
    char_u	buf1[NUMBUFLEN];
    char_u	buf2[NUMBUFLEN];
    char_u	*from, *to, *str;
    vimconv_T	vimconv;
#endif

    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = NULL;

#ifdef FEAT_MBYTE
    str = get_tv_string(&argvars[0]);
    from = enc_canonize(enc_skip(get_tv_string_buf(&argvars[1], buf1)));
    to = enc_canonize(enc_skip(get_tv_string_buf(&argvars[2], buf2)));
    vimconv.vc_type = CONV_NONE;
    convert_setup(&vimconv, from, to);


    if (vimconv.vc_type == CONV_NONE)
	rettv->vval.v_string = vim_strsave(str);
    else
	rettv->vval.v_string = string_convert(&vimconv, str, NULL);

    convert_setup(&vimconv, NULL, NULL);
    vim_free(from);
    vim_free(to);
#endif
}
