makeswapname(fname, ffname, buf, dir_name)
    char_u	*fname;
    char_u	*ffname;
    buf_T	*buf;
    char_u	*dir_name;
{
    char_u	*r, *s;
#ifdef HAVE_READLINK
    char_u	fname_buf[MAXPATHL];
    char_u	*fname_res;
#endif

#if defined(UNIX) || defined(WIN3264)
    s = dir_name + STRLEN(dir_name);
    if (after_pathsep(dir_name, s) && s[-1] == s[-2])
    {
	r = NULL;
	if ((s = make_percent_swname(dir_name, fname)) != NULL)
	{
	    r = modname(s, (char_u *)".swp", FALSE);
	    vim_free(s);
	}
	return r;
    }
#endif

#ifdef HAVE_READLINK


    if (resolve_symlink(fname, fname_buf) == OK)
	fname_res = fname_buf;
    else
	fname_res = fname;
#endif

    r = buf_modname(
#ifdef SHORT_FNAME
	    TRUE,
#else
	    (buf->b_p_sn || buf->b_shortname),
#endif
#ifdef RISCOS

	    ffname,
#else
# ifdef HAVE_READLINK
	    fname_res,
# else
	    fname,
# endif
#endif
	    (char_u *)
#if defined(VMS) || defined(RISCOS)
	    "_swp",
#else
	    ".swp",
#endif
#ifdef SHORT_FNAME
	    FALSE
#else

	    dir_name[0] == '.' && dir_name[1] == NUL
#endif
	       );
    if (r == NULL)
	return NULL;

    s = get_file_in_dir(r, dir_name);
    vim_free(r);
    return s;
}
