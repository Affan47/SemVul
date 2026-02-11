ACL_AuthInfoSetMethod(NSErr_t *errp, PList_t auth_info, ACLMethod_t t)
{
    ACLMethod_t *methodp;
    int rv;

    if (auth_info) {
	rv = PListGetValue(auth_info, ACL_ATTR_METHOD_INDEX, (void **)&methodp,
			    NULL);

	if (rv < 0) {

	    methodp = (ACLMethod_t *)PERM_MALLOC(sizeof(ACLMethod_t));
	    if (!methodp) return -1;
	    *methodp = t;
	    PListInitProp(auth_info, ACL_ATTR_METHOD_INDEX, ACL_ATTR_METHOD, methodp, 0);
	}
	else {

	    if (!methodp) return -1;
	    *methodp = t;
	}
    }
    else {
	return -1;
    }

    return 0;
}
