find_sdp_line_complex(char* p, char* plimit, char * name)
{
	char *cp, *cp1;
	int len =  strlen(name);


	cp = p;
	for (;;) {
		if (cp >= plimit)
			return NULL;
		cp1 = ser_memmem(cp, name, plimit-cp, len);
		if (cp1 == NULL)
			return NULL;


		if (cp1[-1] == '\n' || cp1[-1] == '\r')
			return cp1;


		if (plimit - cp1 < 2)
			return NULL;
		cp = cp1 + 2;
	}
}
