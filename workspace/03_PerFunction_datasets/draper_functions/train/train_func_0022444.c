externalfilegroup_check_authorization(request_rec *r,
	const char *require_args, const void *parsed_require_args)
{
    authnz_external_dir_config_rec *dir= (authnz_external_dir_config_rec *)
	ap_get_module_config(r->per_dir_config, &authnz_external_module);

    authnz_external_svr_config_rec *svr= (authnz_external_svr_config_rec *)
	ap_get_module_config(r->server->module_config, &authnz_external_module);

    char *user= r->user;
    char *extname= dir->group_name;
    const char *extpath, *extmethod;
    const char *filegroup= NULL;
    const char *t, *w;
    int code;


    if ( !user ) return AUTHZ_DENIED_NO_USER;


    if ( !extname ) return AUTHZ_DENIED;


    if (!(extpath= apr_table_get(svr->group_path, extname)) ||
	!(extmethod= apr_table_get(svr->group_method,extname)))
    {
	errno= 0;
	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
	    "invalid GroupExternal keyword (%s)", extname);
	return AUTHZ_DENIED;
    }


    filegroup= authz_owner_get_file_group(r);

    if (!filegroup)

	return AUTHZ_DENIED;


    code= exec_external(extpath, extmethod, r, ENV_GROUP, filegroup);
    if (code == 0) return AUTHZ_GRANTED;

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
	"Authorization of user %s to access %s failed. "
	"User not in Required file group (%s).",
    	r->user, r->uri, filegroup);

    return AUTHZ_DENIED;
}
