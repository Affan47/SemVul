aclDestroyAccessList(acl_access ** list)
{
    acl_access *l = NULL;
    acl_access *next = NULL;
    for (l = *list; l; l = next) {
	debug(28, 3) ("aclDestroyAccessList: '%s'\n", l->cfgline);
	next = l->next;
	aclDestroyAclList(&l->acl_list);
	safe_free(l->cfgline);
	cbdataFree(l);
    }
    *list = NULL;
}
