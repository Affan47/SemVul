aclParseUserMaxIP(void *data)
{
    acl_user_ip_data **acldata = data;
    char *t = NULL;
    CBDATA_INIT_TYPE(acl_user_ip_data);
    if (*acldata) {
	debug(28, 1) ("Attempting to alter already set User max IP acl\n");
	return;
    }
    *acldata = cbdataAlloc(acl_user_ip_data);
    t = strtokFile();
    if (!t)
	goto error;
    debug(28, 5) ("aclParseUserMaxIP: First token is %s\n", t);
    if (strcmp("-s", t) == 0) {
	debug(28, 5) ("aclParseUserMaxIP: Going strict\n");
	(*acldata)->flags.strict = 1;
	t = strtokFile();
	if (!t)
	    goto error;
    }
    (*acldata)->max = xatoi(t);
    debug(28, 5) ("aclParseUserMaxIP: Max IP address's %d\n", (int) (*acldata)->max);
    return;
  error:
    self_destruct();
}
