aclDestroyAclList(acl_list ** head)
{
    acl_list *l;
    for (l = *head; l; l = *head) {
	*head = l->next;
	memFree(l, MEM_ACL_LIST);
    }
}
