gettoken(char *c, off_t len, char *tb, off_t *off) {
	off_t	o=*off,
		ts;
	char	*tbp=NULL;

	while(o<len) {
		switch(c[o]) {

			case(' '):
			case('\t'):
				o++;
				break;

			case('#'):
				while(o<len && c[o] != '\n')
					o++;
				if (o>=len)
					return TOKEN_EOF;
				break;

			case('"'):
				o++;
				ts=o;
				if (tbp)
					return TOKEN_QSTRING_BROKEN;
				tbp=tb;


				while(o<len) {
					switch(c[o]) {
						case('\n'):
							return TOKEN_QSTRING_EOL;
						case('"'):
							*off=++o;
							*tbp++=0x0;
							return TOKEN_QSTRING;
						default:
							*tbp++=c[o++];
							break;
					}
				}
				return TOKEN_QSTRING_EOF;

			case('\n'):
				*off=++o;
				return TOKEN_NEWLINE;
			case(';'):
				*off=++o;
				return TOKEN_COLON;
			case('}'):
				*off=++o;
				return TOKEN_CBRACKET;
			case('{'):
				*off=++o;
				return TOKEN_OBRACKET;

			default:
				tbp=tb;
				while(o<len) {
					switch(c[o]) {

						case(';'):
						case('}'):
						case('{'):
						case('\n'):
						case(' '):
						case('\t'):
						case('#'):
							*off=o;
							*tbp++=0x0;
							return TOKEN_STRING;
						default:
							*tbp++=c[o++];
							break;
					}
				}


		}
	}
	return TOKEN_EOF;
}
