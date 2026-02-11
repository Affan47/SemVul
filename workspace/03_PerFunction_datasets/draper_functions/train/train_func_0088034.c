qt_control(s)
	char *s;
{
	return((boolean)(s[0] == '%' && (s[1] == 'C' || s[1] == 'E')));
}
