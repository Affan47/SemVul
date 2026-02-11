CCcheckfile(av)
    char		*av[];
{
    register char	**strings;
    register char	*p;
    register int	i;
    register int	errors;
    STRING		error;
    SITE		fake;


    strings = SITEreadfile(FALSE);
    fake.Buffer.Size = 0;
    fake.Buffer.Data = NULL;
    for (errors = 0, i = 0; (p = strings[i]) != NULL; i++) {
	if ((error = SITEparseone(p, &fake, (char *)NULL, (char *)NULL)) != NULL) {
	    syslog(L_ERROR, "%s bad_newsfeeds %s", MaxLength(p, p), error);
	    errors++;
	}
	SITEfree(&fake);
    }
    DISPOSE(strings);

    if (errors == 0)
	return NULL;

    if (CCreply.Data == NULL) {

	CCreply.Size = SMBUF;
	CCreply.Data = NEW(char, CCreply.Size);
    }
    else if (CCreply.Size < SMBUF) {
	CCreply.Size = SMBUF;
	RENEW(CCreply.Data, char, CCreply.Size);
    }

    (void)sprintf(CCreply.Data, "1 Found %d errors -- see syslog", errors);
    return CCreply.Data;
}
