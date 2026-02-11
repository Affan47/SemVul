isNumber (char* s)
{
    char* ep = s;
    strtod(s, &ep);
    if (s != ep) {
	while (*ep && isspace(*ep)) ep++;
	if (*ep) return 0;
	else return 1;
    }
    else
	return 0;
}
