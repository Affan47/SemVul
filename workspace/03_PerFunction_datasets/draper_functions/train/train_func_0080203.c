rfc2231(const char *in)
{
	const char *ptr;
	char *ret, *out;
	enum { LANGUAGE, CHARSET, CONTENTS } field;

	if(strstr(in, "*0*=") != NULL) {
		char *p;


		p = ret = cli_malloc(strlen(in) + 16);
		if(ret == NULL) {
            cli_errmsg("rfc2331: out of memory, unable to proceed\n");
			return NULL;
        }

		do {
			switch(*in) {
				default:
					*p++ = *in++;
					continue;
				case '*':
					do
						in++;
					while((*in != '*') && *in);
					if(*in) {
						in++;
						continue;
					}
					*p = '\0';
					break;
				case '=':

					strcpy(p, "=rfc2231failure");
					break;
			}
			break;
		} while(*in);

		cli_dbgmsg("RFC2231 parameter continuations are not yet handled, returning \"%s\"\n",
			ret);
		return ret;
	}

	ptr = strstr(in, "*0=");
	if(ptr != NULL)


		field = CONTENTS;
	else {
		ptr = strstr(in, "*=");
		field = LANGUAGE;
	}

	if(ptr == NULL) {
		out = ret = cli_strdup(in);
		while(*out)
			*out++ &= 0x7F;
		return ret;
	}

	cli_dbgmsg("rfc2231 '%s'\n", in);

	ret = cli_malloc(strlen(in) + 1);

	if(ret == NULL) {
        cli_errmsg("rfc2331: out of memory for ret\n");
		return NULL;
    }


	out = ret;
	while(in != ptr)
		*out++ = *in++;

	*out++ = '=';

	while(*ptr++ != '=')
		;


	while(*ptr) {
		switch(field) {
			case LANGUAGE:
				if(*ptr == '\'')
					field = CHARSET;
				break;
			case CHARSET:
				if(*ptr == '\'')
					field = CONTENTS;
				break;
			case CONTENTS:
				if(*ptr == '%') {
					unsigned char byte;

					if((*++ptr == '\0') || (*ptr == '\n'))
						break;

					byte = hex(*ptr);

					if((*++ptr == '\0') || (*ptr == '\n')) {
						*out++ = byte;
						break;
					}

					byte <<= 4;
					byte += hex(*ptr);
					*out++ = byte;
				} else
					*out++ = *ptr;
		}
		if(*ptr++ == '\0')


			break;
	}

	if(field != CONTENTS) {
		free(ret);
		cli_dbgmsg("Invalid RFC2231 header: '%s'\n", in);
		return cli_strdup("");
	}

	*out = '\0';

	cli_dbgmsg("rfc2231 returns '%s'\n", ret);

	return ret;
}
