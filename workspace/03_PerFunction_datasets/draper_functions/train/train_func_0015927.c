unixgroup_check_authorization(request_rec *r,
        const char *require_args, const void *parsed_require_args)
{

    if ( !r->user ) return AUTHZ_DENIED_NO_USER;

    if (check_unix_group(r,require_args))
	return AUTHZ_GRANTED;

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
        "Authorization of user %s to access %s failed. "
        "User not in Required unix groups (%s).",
        r->user, r->uri, require_args);

    return AUTHZ_DENIED;
}
