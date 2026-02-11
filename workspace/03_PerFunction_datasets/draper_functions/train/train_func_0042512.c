getLine(FILE* fd, fxStackBuffer& buf)
{
    buf.reset();
    for (;;) {
	int c = getc(fd);
	if (c == EOF)
	    return (buf.getLength() > 0);
	c &= 0xff;
	if (c == '\n')
	    break;
	buf.put(c);
    }
    return (true);
}
