ACL_MethodRegister(NSErr_t *errp, const char *name, ACLMethod_t *t)
{
    ACLMethod_t rv;

    ACL_CritEnter();


    rv = (ACLMethod_t) PR_HashTableLookup(ACLMethodHash, name);
    if (rv != NULL) {
	*t = rv;
        ACL_CritExit();
	return 0;
    }


    if (cur_method >= (ACL_MAX_METHOD-1)) {
	ACL_CritExit();
	return -1;
    }


    if (NULL == PR_HashTableAdd(ACLMethodHash, name, (void *)(intptr_t)++cur_method)) {
        ACL_CritExit();
        return -1;
    }
    *t = (ACLMethod_t) (intptr_t)cur_method;

    ACL_CritExit();
    return 0;
}
