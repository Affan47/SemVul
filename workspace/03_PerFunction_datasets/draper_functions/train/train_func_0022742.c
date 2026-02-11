ARTreadschema()
{
    static char			SCHEMA[] = _PATH_SCHEMA;
    register FILE		*F;
    register int		i;
    register char		*p;
    register ARTOVERFIELD	*fp;
    register ARTHEADER		*hp;
    BOOL			ok;
    char			buff[SMBUF];

    if (ARTfields != NULL) {
	DISPOSE(ARTfields);
	ARTfields = NULL;
    }


    if ((F = fopen(SCHEMA, "r")) == NULL)
	return FALSE;
    for (i = 0; fgets(buff, sizeof buff, F) != NULL; i++)
	continue;
    (void)fseek(F, (OFFSET_T)0, SEEK_SET);
    ARTfields = NEW(ARTOVERFIELD, i + 1);


    for (ok = TRUE, fp = ARTfields; fgets(buff, sizeof buff, F) != NULL; ) {

	if ((p = strchr(buff, '\n')) != NULL)
	    *p = '\0';
	if ((p = strchr(buff, COMMENT_CHAR)) != NULL)
	    *p = '\0';
	if (buff[0] == '\0')
	    continue;
	if ((p = strchr(buff, ':')) != NULL) {
	    *p++ = '\0';
	    fp->NeedHeader = EQ(p, "full");
	}
	else
	    fp->NeedHeader = FALSE;
	for (hp = ARTheaders; hp < ENDOF(ARTheaders); hp++)
	    if (EQ(buff, hp->Name)) {
		fp->Header = hp;
		break;
	    }
	if (hp == ENDOF(ARTheaders)) {
	    syslog(L_ERROR, "%s bad_schema unknown header \"%s\"",
		LogName, buff);
	    ok = FALSE;
	    continue;
	}
	fp++;
    }
    fp->Header = NULL;

    (void)fclose(F);
    return ok;
}
