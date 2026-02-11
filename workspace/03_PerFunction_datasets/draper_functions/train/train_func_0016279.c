end_of_function (const char *s)
{
    int ret = 0;

    if (!strncmp(s, "end ", 4)) {
	char word[9];

	if (sscanf(s + 4, "%8s", word) && !strcmp(word, "function")) {
	    ret = 1;
	}
    }

    return ret;
}
