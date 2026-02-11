lak_user_free(
	LAK_USER *user)
{
	if (user == NULL) {
		return;
	}

	memset(user, 0, sizeof(LAK_USER));

	free(user);

	return;
}
