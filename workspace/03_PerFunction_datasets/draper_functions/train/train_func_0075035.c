krb5_config_vget_strings(krb5_context context,
			 const krb5_config_section *c,
			 va_list args)
{
    char **strings = NULL;
    int nstr = 0;
    const krb5_config_binding *b = NULL;
    const char *p;

    while((p = _krb5_config_vget_next(context, c, &b,
				      krb5_config_string, args))) {
	char *tmp = strdup(p);
	char *pos = NULL;
	char *s;
	if(tmp == NULL)
	    goto cleanup;
	s = next_component_string(tmp, " \t", &pos);
	while(s){
	    char **tmp2 = realloc(strings, (nstr + 1) * sizeof(*strings));
	    if(tmp2 == NULL)
		goto cleanup;
	    strings = tmp2;
	    strings[nstr] = strdup(s);
	    nstr++;
	    if(strings[nstr-1] == NULL)
		goto cleanup;
	    s = next_component_string(NULL, " \t", &pos);
	}
	free(tmp);
    }
    if(nstr){
	char **tmp = realloc(strings, (nstr + 1) * sizeof(*strings));
	if(tmp == NULL)
	    goto cleanup;
	strings = tmp;
	strings[nstr] = NULL;
    }
    return strings;
cleanup:
    while(nstr--)
	free(strings[nstr]);
    free(strings);
    return NULL;

}
