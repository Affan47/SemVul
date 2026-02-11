Perl_gv_fetchfile_flags(pTHX_ const char *const name, const STRLEN namelen,
			const U32 flags)
{
    dVAR;
    char smallbuf[128];
    char *tmpbuf;
    const STRLEN tmplen = namelen + 2;
    GV *gv;

    PERL_ARGS_ASSERT_GV_FETCHFILE_FLAGS;
    PERL_UNUSED_ARG(flags);

    if (!PL_defstash)
	return NULL;

    if (tmplen <= sizeof smallbuf)
	tmpbuf = smallbuf;
    else
	Newx(tmpbuf, tmplen, char);

    tmpbuf[0] = '_';
    tmpbuf[1] = '<';
    memcpy(tmpbuf + 2, name, namelen);
    gv = *(GV**)hv_fetch(PL_defstash, tmpbuf, tmplen, TRUE);
    if (!isGV(gv)) {
	gv_init(gv, PL_defstash, tmpbuf, tmplen, FALSE);
#ifdef PERL_DONT_CREATE_GVSV
	GvSV(gv) = newSVpvn(name, namelen);
#else
	sv_setpvn(GvSV(gv), name, namelen);
#endif
    }
    if ((PERLDB_LINE || PERLDB_SAVESRC) && !GvAV(gv))
	    hv_magic(GvHVn(gv_AVadd(gv)), NULL, PERL_MAGIC_dbfile);
    if (tmpbuf != smallbuf)
	Safefree(tmpbuf);
    return gv;
}
