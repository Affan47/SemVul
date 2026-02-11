RClimit(CHANNEL *cp)
{
    REMOTEHOST	*rp;
    int		i;

    for (rp = RCpeerlist, i = RCnpeerlist; --i >= 0; rp++)
	if (network_sockaddr_equal((struct sockaddr *) &cp->Address,
                                   (struct sockaddr *) &rp->Address))
	    return rp->MaxCnx;

    return RemoteLimit;
}
