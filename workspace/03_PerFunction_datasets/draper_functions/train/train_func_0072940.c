MAPread(name)
    char		*name;
{
    register FILE	*F;
    register int	i;
    register PAIR	*mp;
    register char	*p;
    char		buff[BUFSIZ];

    if (MAPdata != NULL)
	MAPfree();


    if ((F = fopen(name, "r")) == NULL) {
	(void)fprintf(stderr, "Can't open %s, %s\n", name, strerror(errno));
	exit(1);
    }
    for (i = 0; fgets(buff, sizeof buff, F) != NULL; i++)
	continue;
    mp = MAPdata = NEW(PAIR, i + 1);


    (void)fseek(F, (OFFSET_T)0, SEEK_SET);
    while (fgets(buff, sizeof buff, F) != NULL) {
	if ((p = strchr(buff, '\n')) != NULL)
	    *p = '\0';
	if (buff[0] == '\0'
	 || buff[0] == COMMENT_CHAR
	 || (p = strchr(buff, ':')) == NULL)
	    continue;
	*p++ = '\0';
	mp->First = buff[0];
	mp->Key = COPY(buff);
	mp->Value = COPY(p);
	mp++;
    }
    (void)fclose(F);
    MAPend = mp;
}
