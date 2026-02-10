unquotestrdup(char *s)
{
	char *t, *ret;
	int quoting;

	ret = s = strdup(s);
	if(ret == nil)
		return ret;
	quoting = 0;
	t = s;
	while(*t!='\0' && (quoting || (*t!=' ' && *t!='\t'))){
		if(*t != '\''){
			*s++ = *t++;
			continue;
		}

		if(!quoting){
			quoting = 1;
			t++;
			continue;
		}

		if(t[1] != '\''){

			t++;
			quoting = 0;
			continue;
		}

		t++;
		*s++ = *t++;
	}
	if(t != s)
		memmove(s, t, strlen(t)+1);
	return ret;
}
