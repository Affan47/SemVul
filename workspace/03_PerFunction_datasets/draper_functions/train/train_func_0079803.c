__aclinit__RegisterAttributes(void)
{

	ACLMethod_t	methodinfo;
	NSErr_t		errp;
	int		rv;

	memset (&errp, 0, sizeof(NSErr_t));

	rv = ACL_MethodRegister(&errp, DS_METHOD, &methodinfo);
	if (rv < 0) {
		acl_print_acllib_err(&errp, NULL);
		slapi_log_error(SLAPI_LOG_FATAL, plugin_name,
			  "Unable to Register the methods\n");
		return ACL_ERR;
	}
	rv = ACL_MethodSetDefault (&errp,  methodinfo);
	if (rv < 0) {
		acl_print_acllib_err(&errp, NULL);
		slapi_log_error(SLAPI_LOG_FATAL, plugin_name,
			  "Unable to Set the default method\n");
		return ACL_ERR;
	}
        rv = ACL_AttrGetterRegister(&errp, ACL_ATTR_IP, DS_LASIpGetter,
				methodinfo, ACL_DBTYPE_ANY, ACL_AT_FRONT, NULL);
	if (rv < 0) {
		acl_print_acllib_err(&errp, NULL);
		slapi_log_error(SLAPI_LOG_FATAL, plugin_name,
			  "Unable to Register Attr ip\n");
		return ACL_ERR;
	}
        rv = ACL_AttrGetterRegister(&errp, ACL_ATTR_DNS, DS_LASDnsGetter,
				methodinfo, ACL_DBTYPE_ANY, ACL_AT_FRONT, NULL);
	if (rv < 0) {
		acl_print_acllib_err(&errp, NULL);
		slapi_log_error(SLAPI_LOG_FATAL, plugin_name,
			  "Unable to Register Attr dns\n");
		return ACL_ERR;
	}
	return ACL_OK;
}
