config_fgets(char *str, size_t len, struct fileptr *ptr)
{


    if(ptr->f != NULL)
	return fgets(str, len, ptr->f);
    else {

	const char *p;
	ssize_t l;
	if(*ptr->s == '\0')
	    return NULL;
	p = ptr->s + strcspn(ptr->s, "\n");
	if(*p == '\n')
	    p++;
	l = min(len, (size_t)(p - ptr->s));
	if(len > 0) {
	    memcpy(str, ptr->s, l);
	    str[l] = '\0';
	}
	ptr->s = p;
	return str;
    }
}
