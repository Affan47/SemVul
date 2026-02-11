PLartfilter(const ARTDATA *data, char *artBody, long artLen, int lines)
{
    dSP;
    const ARTHEADER * hp;
    const HDRCONTENT *hc = data->HdrContent;
    HV *        hdr;
    CV *        filter;
    int         i, rc;
    char *      p;
    static char buf[256];
    bool        failure;

    if (!PerlFilterActive) return NULL;
    filter = perl_get_cv("filter_art", 0);
    if (!filter) return NULL;


    hdr = perl_get_hv("hdr", 1);
    for (i = 0 ; i < MAX_ARTHEADER ; i++) {
	if (HDR_FOUND(i)) {
	    hp = &ARTheaders[i];
            (void) hv_store(hdr, (char *) hp->Name, hp->Size, newSVpv(HDR(i), 0), 0);
	}
    }


    if (artBody) {
#if (PERL_REVISION == 5) && ((PERL_VERSION < 7) || ((PERL_VERSION == 7) && (PERL_SUBVERSION < 1)))
        (void) hv_store(hdr, "__BODY__", 8, newSVpv(artBody, artLen), 0);
#else
        (void) hv_store(hdr, "__BODY__", 8, newSVpvn_share(artBody, artLen, 42), 0);
#endif
    }

    (void) hv_store(hdr, "__LINES__", 9, newSViv(lines), 0);

    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    PUTBACK;
    rc = perl_call_sv((SV *) filter, G_EVAL|G_SCALAR|G_NOARGS);
    SPAGAIN;

    hv_undef(hdr);


    buf[0] = '\0';
    if (SvTRUE(ERRSV)) {
        failure = true;
        syslog(L_ERROR, "Perl function filter_art died on article %s: %s",
               HDR_FOUND(HDR__MESSAGE_ID) ? HDR(HDR__MESSAGE_ID) : "?",
               SvPV(ERRSV, PL_na));
        (void) POPs;
    } else {
        failure = false;
        if (rc == 1) {
            p = POPp;
            if (p && *p)
                strlcpy(buf, p, sizeof(buf));
        }
    }

    PUTBACK;
    FREETMPS;
    LEAVE;

    if (failure)
        PerlFilter(false);

    return (buf[0] != '\0') ? buf : NULL;
}
