parseKind(Sfio_t * str)
{
    int c;
    char buf[BSIZE];
    case_t cs = Error;

    c = skipWS(str);
    if (c < 0)
	return Eof;
    if (!isalpha(c)) {
	error(ERROR_ERROR,
	      "expected keyword BEGIN/END/N/E...; found '%c', line %d", c,
	      lineno);
	return Error;
    }

    kwLine = lineno;
    parseID(str, c, buf, BSIZE);
    switch (c) {
    case 'B':
	if (strcmp(buf, "BEGIN") == 0)
	    cs = Begin;
	if (strcmp(buf, "BEG_G") == 0)
	    cs = BeginG;
	break;
    case 'E':
	if (buf[1] == '\0')
	    cs = Edge;
	if (strcmp(buf, "END") == 0)
	    cs = End;
	if (strcmp(buf, "END_G") == 0)
	    cs = EndG;
	break;
    case 'N':
	if (buf[1] == '\0')
	    cs = Node;
	break;
    }
    if (cs == Error)
	error(ERROR_ERROR, "unexpected keyword \"%s\", line %d", buf,
	      kwLine);
    return cs;
}
