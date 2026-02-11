add_authgroup(AUTHGROUP *group)
{
    int i;

    if (auth_realms == NULL) {
	i = 0;
	auth_realms = xmalloc(2 * sizeof(AUTHGROUP *));
    } else {
	for (i = 0; auth_realms[i]; i++)
	    ;
        auth_realms = xrealloc(auth_realms, (i + 2) * sizeof(AUTHGROUP *));
    }
    auth_realms[i] = group;
    auth_realms[i+1] = 0;
}
