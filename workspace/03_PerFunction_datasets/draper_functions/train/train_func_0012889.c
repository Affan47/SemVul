authenticate_user(const char *username, const char *pwd)
{
    char salt[12];
    int i;

    for (i = 0; i < numusers; i++) {
	if (userdb[i] == NULL)
	    continue;
	if (strcmp(username, userdb[i]->username) == 0) {
	    strcpy(salt, userdb[i]->pwdhash);
	    salt[2] = '\0';
	    if (strcmp(userdb[i]->pwdhash, crypt(pwd, salt)) == 0)
		return 1;
	}
    }
    return 0;
}
