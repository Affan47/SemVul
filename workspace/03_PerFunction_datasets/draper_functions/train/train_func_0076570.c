kerberos5_status(Authenticator *ap, char *name, size_t name_sz, int level)
{
    if (level < AUTH_USER)
	return(level);

    if (UserNameRequested &&
	krb5_kuserok(context,
		     ticket->client,
		     UserNameRequested))
	{
	    strlcpy(name, UserNameRequested, name_sz);
#if defined(DCE)
	    dfsk5ok = 1;
#endif
	    return(AUTH_VALID);
	} else
	    return(AUTH_USER);
}
