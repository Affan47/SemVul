clientAccessCheckDone2(int answer, void *data)
{
    clientHttpRequest *http = data;
    err_type page_id;
    http_status status;
    ErrorState *err = NULL;
    char *proxy_auth_msg = NULL;
    debug(33, 2) ("The request %s %s is %s, because it matched '%s'\n",
	http->request->method->string, http->uri,
	answer == ACCESS_ALLOWED ? "ALLOWED" : "DENIED",
	AclMatchedName ? AclMatchedName : "NO ACL's");
    proxy_auth_msg = authenticateAuthUserRequestMessage(http->conn->auth_user_request ? http->conn->auth_user_request : http->request->auth_user_request);
    http->acl_checklist = NULL;
    if (answer == ACCESS_ALLOWED) {
	clientCheckNoCache(http);
    } else {
	int require_auth = (answer == ACCESS_REQ_PROXY_AUTH || aclIsProxyAuth(AclMatchedName));
	debug(33, 5) ("Access Denied: %s\n", http->uri);
	debug(33, 5) ("AclMatchedName = %s\n",
	    AclMatchedName ? AclMatchedName : "<null>");
	if (require_auth)
	    debug(33, 5) ("Proxy Auth Message = %s\n",
		proxy_auth_msg ? proxy_auth_msg : "<null>");


	page_id = aclGetDenyInfoPage(&Config.denyInfoList, AclMatchedName, answer != ACCESS_REQ_PROXY_AUTH);
	http->log_type = LOG_TCP_DENIED;
	http->entry = clientCreateStoreEntry(http, http->request->method,
	    null_request_flags);
	if (require_auth) {
	    if (!http->flags.accel) {

		status = HTTP_PROXY_AUTHENTICATION_REQUIRED;
	    } else {

		status = HTTP_UNAUTHORIZED;
	    }
	    if (page_id == ERR_NONE)
		page_id = ERR_CACHE_ACCESS_DENIED;
	} else {
	    status = HTTP_FORBIDDEN;
	    if (page_id == ERR_NONE)
		page_id = ERR_ACCESS_DENIED;
	}
	err = errorCon(page_id, status, http->orig_request);
	if (http->conn->auth_user_request)
	    err->auth_user_request = http->conn->auth_user_request;
	else if (http->request->auth_user_request)
	    err->auth_user_request = http->request->auth_user_request;

	if (err->auth_user_request)
	    authenticateAuthUserRequestLock(err->auth_user_request);
	err->callback_data = NULL;
	errorAppendEntry(http->entry, err);
    }
}
