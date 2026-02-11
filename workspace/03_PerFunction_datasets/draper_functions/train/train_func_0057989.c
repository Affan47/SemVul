krb5_config_parse_debug (struct fileptr *f,
			 krb5_config_section **res,
			 unsigned *lineno,
			 const char **err_message)
{
    krb5_config_section *s = NULL;
    krb5_config_binding *b = NULL;
    char buf[KRB5_BUFSIZ];
    krb5_error_code ret;

    while (config_fgets(buf, sizeof(buf), f) != NULL) {
	char *p;

	++*lineno;
	buf[strcspn(buf, "\r\n")] = '\0';
	p = buf;
	while(isspace((unsigned char)*p))
	    ++p;
	if (*p == '#' || *p == ';')
	    continue;
	if (*p == '[') {
	    ret = parse_section(p, &s, res, err_message);
	    if (ret)
		return ret;
	    b = NULL;
	} else if (*p == '}') {
	    *err_message = "unmatched }";
	    return EINVAL;
	} else if(*p != '\0') {
	    if (s == NULL) {
		*err_message = "binding before section";
		return EINVAL;
	    }
	    ret = parse_binding(f, lineno, p, &b, &s->u.list, err_message);
	    if (ret)
		return ret;
	}
    }
    return 0;
}
