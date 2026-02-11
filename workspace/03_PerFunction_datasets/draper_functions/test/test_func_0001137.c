pam_auth(void *instance, REQUEST *request)
{
	int	r;
	VALUE_PAIR *pair;
	rlm_pam_t *data = (rlm_pam_t *) instance;

	const char *pam_auth_string = data->pam_auth_name;


	if (!request->username) {
		radlog(L_AUTH, "rlm_pam: Attribute \"User-Name\" is required for authentication.");
		return RLM_MODULE_INVALID;
	}


	if (!request->password) {
		radlog(L_AUTH, "rlm_pam: Attribute \"User-Password\" is required for authentication.");
		return RLM_MODULE_INVALID;
	}


	if (request->password->attribute != PW_USER_PASSWORD) {
		radlog(L_AUTH, "rlm_pam: Attribute \"User-Password\" is required for authentication.  Cannot use \"%s\".", request->password->name);
		return RLM_MODULE_INVALID;
	}


	pair = pairfind(request->config_items, PAM_AUTH_ATTR);
	if (pair) pam_auth_string = (char *)pair->vp_strvalue;

	r = pam_pass((char *)request->username->vp_strvalue,
		     (char *)request->password->vp_strvalue,
		     pam_auth_string);

	if (r == 0) {
		return RLM_MODULE_OK;
	}
	return RLM_MODULE_REJECT;
}
