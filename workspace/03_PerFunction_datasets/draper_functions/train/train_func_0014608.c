aisc_server_load_token(FILE *fd,char *buffer, int maxsize)
	{
	char *p;
	int c;
	int in_brackets = 0;
	p = buffer;
	while(maxsize-->0){
		c = getc(fd);
		if (c==EOF) { *p=0; return EOF;}
		else if(in_brackets) {
		    if (c=='\\') { c = getc(fd); *(p++) = c; continue; }
		    if (c!='}') *(p++) = c;else {*p=0;return 0;}
		}else if (c=='{'){ if (p!=buffer) {*(p++) = '{';*p=0;return 0;}
		                    else    in_brackets = 1; }
		else if (c==' '){ if (p!=buffer) {*p=0;return 0;} }
		else if (c=='\n'){ if (p!=buffer) {*p=0;return 0;} }
		else if (c=='}') {*(p++) = '}'; *p=0;return 0;}
		else *(p++) = c;
	}
	*p = 0; return EOF;
	}
