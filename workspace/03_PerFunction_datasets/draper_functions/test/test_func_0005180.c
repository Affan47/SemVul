cut_trailing_point (char *s)
{
    int n = strlen(s);

    if (s[n-1] == '.' || s[n-1] == ',') {
	s[n-1] = '\0';
    }

    return s;
}
