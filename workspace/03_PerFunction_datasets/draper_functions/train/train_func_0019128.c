RChostname(cp)
    register CHANNEL	*cp;
{
    static char		buff[SMBUF];
    register REMOTEHOST	*rp;
    register int	i;

    for (rp = RCpeerlist, i = RCnpeerlist; --i >= 0; rp++)

	if (cp->Address.s_addr == rp->Address.s_addr)
	    return rp->Name;
    (void)strcpy(buff, inet_ntoa(cp->Address));
    return buff;
}
