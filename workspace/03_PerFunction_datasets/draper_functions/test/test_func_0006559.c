vim_setenv(name, val)
    char_u	*name;
    char_u	*val;
{
#ifdef HAVE_SETENV
    mch_setenv((char *)name, (char *)val, 1);
#else
    char_u	*envbuf;


    envbuf = alloc((unsigned)(STRLEN(name) + STRLEN(val) + 2));
    if (envbuf != NULL)
    {
	sprintf((char *)envbuf, "%s=%s", name, val);
	putenv((char *)envbuf);
    }
#endif
#ifdef FEAT_GETTEXT


    if (*val != NUL && STRICMP(name, "VIMRUNTIME") == 0)
    {
	char_u	*buf = concat_str(val, (char_u *)"/lang");

	if (buf != NULL)
	{
	    bindtextdomain(VIMPACKAGE, (char *)buf);
	    vim_free(buf);
	}
    }
#endif
}
