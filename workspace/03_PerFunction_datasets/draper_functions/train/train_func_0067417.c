aclChecklistCreate(const acl_access * A, request_t * request, const char *ident)
{
    int i;
    aclCheck_t *checklist;
    checklist = cbdataAlloc(aclCheck_t);
    checklist->access_list = A;


    cbdataLock(A);
    if (request)
	checklist->request = requestLink(request);
    for (i = 0; i < ACL_ENUM_MAX; i++)
	checklist->state[i] = ACL_LOOKUP_NONE;
#if USE_IDENT
    if (ident)
	xstrncpy(checklist->rfc931, ident, USER_IDENT_SZ);
#endif
    checklist->auth_user_request = NULL;
    return checklist;
}
