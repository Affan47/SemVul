attr_getter_is_matching(NSErr_t *errp, ACLAttrGetter_t *getter,
				   ACLMethod_t method, ACLDbType_t dbtype)
{
    if ((ACL_MethodIsEqual(errp, getter->method, method) ||
	 ACL_MethodIsEqual(errp, getter->method, ACL_METHOD_ANY)) &&
	(ACL_DbTypeIsEqual(errp, getter->dbtype, dbtype) ||
	 ACL_DbTypeIsEqual(errp, getter->dbtype, ACL_DBTYPE_ANY)))
    {
	return 1;
    }
    else {
	return 0;
    }
}
