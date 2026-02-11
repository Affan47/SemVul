get_token(char **c, char **p)
{
    int	len;

    if (**c == '"') {
	*p = ++*c;
	while (**p != '\0' && **p != '"')
	    (*p)++;
	if (**p == '\0')
	    len = -1;
	else
	    len = (*p)++ - *c;
    } else {
	*p = *c;
	while (**p != '\0' && **p != ' ' &&
	       **p != '\t' && **p != '/' &&
	       **p != ';' && **p != '(' &&
	       **p != '=' && **p != '"')
	    (*p)++;
	len = *p - *c;
    }

    return len;
}
