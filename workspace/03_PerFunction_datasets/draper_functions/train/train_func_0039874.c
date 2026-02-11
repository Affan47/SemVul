authenticateUserAuthenticated(auth_user_request_t * auth_user_request)
{
    if (!authenticateValidateUser(auth_user_request))
	return 0;
    if (auth_user_request->lastReply == AUTH_AUTHENTICATED)
	return 1;
    if (auth_user_request->auth_user->auth_module > 0)
	return authscheme_list[auth_user_request->auth_user->auth_module - 1].authenticated(auth_user_request);
    else
	return 0;
}
