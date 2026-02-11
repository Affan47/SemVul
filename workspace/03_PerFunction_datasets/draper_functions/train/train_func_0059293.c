aclutil_print_resource( struct acl_pblock *aclpb, const char *right , char *attr, char *clientdn )
{

	char		str[BUFSIZ];
	const char  *dn;


	if ( aclpb == NULL) return;

	if ( ! slapi_is_loglevel_set ( SLAPI_LOG_ACL ) )
		return;

	slapi_log_error (SLAPI_LOG_ACL, plugin_name, "    ************ RESOURCE INFO STARTS *********\n");
	slapi_log_error (SLAPI_LOG_ACL, plugin_name, "    Client DN: %s\n",
		   clientdn ? clientdn : "NULL");
	aclutil__access_str (aclpb->aclpb_access, str);
    aclutil__typestr (aclpb->aclpb_res_type, &str[strlen(str)]);
	slapi_log_error (SLAPI_LOG_ACL, plugin_name, "    resource type:%d(%s)\n",
		   aclpb->aclpb_res_type, str);

	dn = slapi_sdn_get_dn ( aclpb->aclpb_curr_entry_sdn );
	slapi_log_error (SLAPI_LOG_ACL, plugin_name, "    Slapi_Entry DN: %s\n",
		   dn ? dn  : "NULL");

	slapi_log_error (SLAPI_LOG_ACL, plugin_name, "    ATTR: %s\n", attr ? attr : "NULL");
	slapi_log_error (SLAPI_LOG_ACL, plugin_name, "    rights:%s\n", right ? right: "NULL");
	slapi_log_error (SLAPI_LOG_ACL, plugin_name, "    ************ RESOURCE INFO ENDS   *********\n");
}
