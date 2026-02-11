addstr(STRINGHEAD *hp, char *str)
{
	char *retstr;
	char *list;
	long newsize;
	size_t len;

	if ((str == NULL) || (*str == '\0'))
		return NULL;
	len = strlen(str) + 1;
	if (hp->h_avail <= len) {
		newsize = len + 2000 + hp->h_used + hp->h_avail;
		list = (char *)realloc(hp->h_list, newsize);
		if (list == NULL)
			return NULL;
		hp->h_list = list;
		hp->h_avail = newsize - hp->h_used;
	}
	retstr = hp->h_list + hp->h_used;
	hp->h_used += len;
	hp->h_avail -= len;
	hp->h_count++;
	strcpy(retstr, str);
	retstr[len] = '\0';
	return retstr;
}
