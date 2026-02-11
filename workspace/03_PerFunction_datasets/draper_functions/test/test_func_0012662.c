SITEfunnelpatch()
{
    register int	i;
    register int	length;
    register SITE	*sp;
    SITE		*funnel;
    BOOL		result;


    for (length = 0, i = nSites, sp = Sites; --i >= 0; sp++)
	if (sp->Name != NULL)
	    length += 1 + strlen(sp->Name);


    for (result = TRUE, i = nSites, sp = Sites; --i >= 0; sp++) {
	if (sp->Name == NULL || sp->Type != FTfunnel)
	    continue;


	if (sp->Param == NULL) {
	    syslog(L_FATAL, "%s funnel NULL", sp->Name);
	    SITEfree(sp);
	    result = FALSE;
	    continue;
	}
	if ((funnel = SITEfind(sp->Param)) == NULL) {
	    syslog(L_FATAL, "%s funnel_bad", sp->Name);
	    SITEfree(sp);
	    result = FALSE;
	    continue;
	}
	if (funnel->Type == FTfunnel) {
	    syslog(L_FATAL, "%s funnels to funnel %s", sp->Name, funnel->Name);
	    SITEfree(sp);
	    result = FALSE;
	    continue;
	}
	if (funnel->FNLnames.Data == NULL) {
	    funnel->FNLnames.Size = length;
	    funnel->FNLnames.Data = NEW(char, length);
	}
	else if (funnel->FNLnames.Size != length) {
	    funnel->FNLnames.Size = length;
	    RENEW(funnel->FNLnames.Data, char, length);
	}
	sp->Funnel = funnel - Sites;
    }

    return result;
}
