parseNum(const std::string& str, int base)
{
	int ret=0;
	int sign = 1;
	const char *c = str.c_str();
	static std::string digits = "0123456789abcdef";
	if (*c == '-')
	{
		sign = -1;
		c++;
	}
	for ( ; *c != '\0' ; c++)
	{
		char pc = *c;
		if (base==10 && !isdigit(pc)) break;
		if ( (pc <= 'Z') && (pc >= 'A') ) pc+=('a'-'A');
		ret *= base;

		size_t i = digits.find_first_of(pc) ;
		ret += i;
	}
	return ret*sign;
}
