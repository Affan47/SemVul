get_text(char *input, char *end, char *dest, int dlen)
{
    int state = 0;
    int cnt = 0;

    while (*input) {
	switch (state) {
	case 0:
	    if (*input == '<')
		state = 1;
	    else {
		if (cnt < (dlen - 1))
		    dest[cnt++] = *input;
	    }
	    break;

	case 1:
	    if (*input == '/')
		state = 2;
	    else if (*input == '>')
		state = 0;
	    break;

	case 2:
	    if (strncasecmp(input, end, strlen(end)) == 0) {
		dest[cnt++] = 0;
		return;
	    }
	    break;
	}

	input++;
    }

}
