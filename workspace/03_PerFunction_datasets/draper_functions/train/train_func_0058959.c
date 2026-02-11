convchar(int *p)
{	switch (yytext[(*p)++])
	{	case 'a':	return '\a';
		case 'b':	return '\b';
		case 'f':	return '\f';
		case 'n':	return '\n';
		case 'r':	return '\r';
		case 't':	return '\t';
		case 'v':	return '\v';
		case 'x':	return hexchar(p);
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':	(*p)--;
				return octchar(p);
		default:	return yytext[*p-1];
	}
}
