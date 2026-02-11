set_text(char *in)
{
	int in_length;

	in_length = strlen(in);
	if (in_length > length)
		Assert(0);

	strcpy(text, in);

	if (flags & UI_INPUTBOX_FLAG_PASSWD) {
		memset(passwd_text, INPUTBOX_PASSWD_CHAR, strlen(text));
		passwd_text[strlen(text)] = 0;
	}

	position = in_length;
}
