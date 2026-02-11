trim_http(char* buf)
{
    enum { NORMAL, HTTP } state = NORMAL;
    char* e = buf;
    char* d = buf;

    while (*e) {
	if (*e == '<' && (toupper(e[1]) == 'I' || e[1] == '/'))
	    state = HTTP;
	else if (state == HTTP)
	{
	    if (*e == '>')
		state = NORMAL;
	}
	else
	    *d++ = *e;
        e++;
    }
    *d = 0;
}
