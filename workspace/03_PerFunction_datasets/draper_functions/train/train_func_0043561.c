authenticateUserUsername(auth_user_t * auth_user)
{
    if (!auth_user)
	return NULL;
    if (auth_user->auth_module > 0)
	return authscheme_list[auth_user->auth_module - 1].authUserUsername(auth_user);
    return NULL;
}
