GetFQDN()
{
    static char		buff[SMBUF];
    struct hostent	*hp;
    char		*p;
    char		**ap;
#if	0

    char		temp[SMBUF + 2];
#endif


    if (buff[0])
	return buff;


    if (gethostname(buff, (int)sizeof buff) < 0)
	return NULL;
    if (strchr(buff, '.') != NULL)
	return buff;


    if ((hp = gethostbyname(buff)) == NULL)
	return NULL;
#if	0


    if (strchr(hp->h_name, '.') == NULL) {

	(void)strncpy(temp, buff, sizeof(temp) - 1);
	temp[sizeof(temp) - 1] = '\0';
	(void)strncat(temp, ".", sizeof(temp) - strlen(temp) - 1);
	hp = gethostbyname(temp);
    }
#endif


    if (hp != NULL && strchr(hp->h_name, '.') != NULL) {
	if (strlen(hp->h_name) < sizeof buff - 1)
	    return strcpy(buff, hp->h_name);

	buff[0] = '\0';
	return hp->h_name;
    }


    if ((ap = hp->h_aliases) != NULL)
	while ((p = *ap++) != NULL)
	    if (strchr(p, '.') != NULL) {

		if (strlen(p) < sizeof buff - 1)
		    return strcpy(buff, p);
		buff[0] = '\0';
		return p ;
	    }


    if ((p = GetFileConfigValue(_CONF_DOMAIN)) == NULL || *p == '\0')
	return NULL;
    if (strlen(buff) + 1 + strlen(p) > sizeof buff - 1)

	return NULL;
    (void)strcat(buff, ".");
    (void)strcat(buff, p);
    return buff;
}
