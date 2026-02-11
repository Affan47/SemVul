viminfo_encoding(virp)
    vir_T	*virp;
{
#ifdef FEAT_MBYTE
    char_u	*p;
    int		i;

    if (get_viminfo_parameter('c') != 0)
    {
	p = vim_strchr(virp->vir_line, '=');
	if (p != NULL)
	{

	    ++p;
	    for (i = 0; vim_isprintc(p[i]); ++i)
		;
	    p[i] = NUL;

	    convert_setup(&virp->vir_conv, p, p_enc);
	}
    }
#endif
    return viminfo_readline(virp);
}
