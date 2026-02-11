GetFileConfigValue(value)
    register char	*value;
{
    register FILE	*F;
    register int	i;
    register char	*p;
    register char	c;


    if ((F = fopen(_PATH_CONFIG, "r")) != NULL) {
	c = *value;
	i = strlen(value);
	while (fgets(ConfigBuff, sizeof ConfigBuff, F) != NULL) {
	    if ((p = strchr(ConfigBuff, '\n')) != NULL)
		*p = '\0';
	    if (ConfigBuff[0] == '\0' || ConfigBuff[0] == COMMENT_CHAR)
		continue;
	    if (ConfigBuff[0] == c
	     && ConfigBuff[i] == ':'
	     && EQn(ConfigBuff, value, i)) {
		(void)fclose(F);
		for (p = &ConfigBuff[i + 1]; ISWHITE(*p); p++)
		    continue;
		return p;
	    }
	}
	(void)fclose(F);
    }
    return NULL;
}
