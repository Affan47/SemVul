lcl_fix_polish(char *str)
{
	for (; *str; str++) {
		if(*str == '\xA2')
			*str = '\xF3';
		else if(*str == '\x88')
			*str = '\xEA';
	}
}
