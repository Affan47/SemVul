aclLookupIdentDone(const char *ident, void *data)
{
    aclCheck_t *checklist = data;
    if (ident) {
	xstrncpy(checklist->rfc931, ident, USER_IDENT_SZ);
#if DONT
	xstrncpy(checklist->request->authuser, ident, USER_IDENT_SZ);
#endif
    } else {
	xstrncpy(checklist->rfc931, dash_str, USER_IDENT_SZ);
    }


    if (cbdataValid(checklist->conn) && !checklist->conn->rfc931[0])
	xstrncpy(checklist->conn->rfc931, checklist->rfc931, USER_IDENT_SZ);
    aclCheck(checklist);
}
