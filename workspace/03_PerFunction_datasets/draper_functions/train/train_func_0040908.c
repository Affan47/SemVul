skipWS(Sfio_t * str)
{
    int c;

    while (1) {
	c = readc(str, 0);
	if (!isspace(c)) {
	    return c;
	}
    }
}
