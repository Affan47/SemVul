ACL_AssertAcllist(ACLListHandle_t *acllist)
{
    ACLWrapper_t *wrap;

    if (acllist == ACL_LIST_NO_ACLS) return 1;
    PR_ASSERT(acllist);
    PR_ASSERT(acllist->acl_list_head);
    PR_ASSERT(acllist->acl_list_tail);
    PR_ASSERT(acllist->acl_count);
    PR_ASSERT(acllist->ref_count > 0);

    for (wrap=acllist->acl_list_head; wrap; wrap=wrap->wrap_next) {
	PR_ASSERT(ACL_AssertAcl(wrap->acl));
    }


    PR_ASSERT(acllist->acl_count < 10);

    return 1;
}
