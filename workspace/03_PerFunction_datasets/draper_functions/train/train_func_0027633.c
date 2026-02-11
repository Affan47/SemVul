nssList_AddUnique(nssList *list, void *data)
{
    PRStatus nssrv;
    nssListElement *node;
    NSSLIST_LOCK_IF(list);
    node = nsslist_get_matching_element(list, data);
    if (node) {

	NSSLIST_UNLOCK_IF(list);
	return PR_SUCCESS;
    }
    nssrv = nsslist_add_element(list, data);
    NSSLIST_UNLOCK_IF(list);
    return nssrv;
}
