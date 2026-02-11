extc_mb(String *sp) {
    wchar_t c = '\0';
    size_t size;
    mbstate_t st;
    memset(&st, 0, sizeof(st));
    size = mbrtowc(&c, *sp, MAX_CHAR_ENCODING, &st);
    switch (size) {
    case (size_t)(-1):
	errno = 0;

    case (size_t)(-2):
	c = BAD_CHAR;
	(*sp)++;
	break;
    case 0:
	(*sp)++;
	break;
    default:
	*sp += size;
    }
    return c;
}
