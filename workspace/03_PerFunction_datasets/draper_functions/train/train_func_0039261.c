cha_litmatch(const char *string, int num, ...)
{
    va_list ap;
    enum cha_lit_str lit;

    va_start(ap, num);
    for (; num > 0; num--) {
	lit = va_arg(ap, enum cha_lit_str);
	if (!strcmp(string, cha_literal[lit][1]) ||
	    !strcmp(string, cha_literal[lit][2]))
	    return 1;
    }
    va_end(ap);

    return 0;
}
