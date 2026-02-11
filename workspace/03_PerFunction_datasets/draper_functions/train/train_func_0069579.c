SEC_GetPassword(FILE *input, FILE *output, char *prompt,
			       PRBool (*ok)(char *))
{
#if defined(_WINDOWS)
    int isTTY = (input == stdin);
#define echoOn(x)
#define echoOff(x)
#else
    int infd  = fileno(input);
    int isTTY = isatty(infd);
#endif
    char phrase[200] = {'\0'};

    for (;;) {

	if (isTTY) {
	    fprintf(output, "%s", prompt);
            fflush (output);
	    echoOff(infd);
	}

	QUIET_FGETS ( phrase, sizeof(phrase), input);

	if (isTTY) {
	    fprintf(output, "\n");
	    echoOn(infd);
	}


	phrase[PORT_Strlen(phrase)-1] = 0;


	if (!(*ok)(phrase)) {

	    if (!isTTY) return 0;
	    fprintf(output, "Password must be at least 8 characters long with one or more\n");
	    fprintf(output, "non-alphabetic characters\n");
	    continue;
	}
	return (char*) PORT_Strdup(phrase);
    }
}
