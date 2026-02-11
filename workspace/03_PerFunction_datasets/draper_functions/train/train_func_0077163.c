last_char(void)
{
    size_t len = strlen(bufptr);
    while (len--) {
	if (!isspace(UChar(bufptr[len])))
	    return bufptr[len];
    }
    return 0;
}
