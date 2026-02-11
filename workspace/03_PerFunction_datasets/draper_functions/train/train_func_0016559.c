filter_password_chars (char *password,
                       int length)
{
	int i, j;


	for (i = 0, j = 0; i < length; i++) {
		if (password[i] >= 32 && password[i] <= 122 &&
		    strchr (" !'\"$`", password[i]) == NULL)
			password[j++] = password[i];
	}


	return j;
}
