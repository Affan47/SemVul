change_token(const char * word)
{
	if (word) {
		char * r = mystrdup(line[actual] + head);
		strcpy(line[actual] + token, word);
		strcat(line[actual], r);
		head = token;
		free(r);
		return 1;
	}
	return 0;
}
