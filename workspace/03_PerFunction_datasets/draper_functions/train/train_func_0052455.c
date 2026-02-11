NCsetup(void)
{
    char		*p;
    char		buff[SMBUF];


    p = innconf->pathhost;
    if (p == NULL)

	p = Path.data;
    snprintf(buff, sizeof(buff), "%d %s InterNetNews server %s ready (transit mode)",
             NNTP_OK_BANNER_POST, p, INN_VERSION_STRING);
    NCgreeting = xstrdup(buff);
}
