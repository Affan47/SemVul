auth_status(void)
{
    Authenticator *ap;
    int i, mask;

    if (i_wont_support == -1)
	printf("Authentication disabled\n");
    else
	printf("Authentication enabled\n");

    mask = 0;
    for (ap = authenticators; ap->type; ap++) {
	if ((mask & (i = typemask(ap->type))) != 0)
	    continue;
	mask |= i;
	printf("%s: %s\n", AUTHTYPE_NAME(ap->type),
	       (i_wont_support & typemask(ap->type)) ?
	       "disabled" : "enabled");
    }
    return(1);
}
