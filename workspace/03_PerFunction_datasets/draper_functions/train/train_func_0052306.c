krb5_config_vget_int_default (krb5_context context,
			      const krb5_config_section *c,
			      int def_value,
			      va_list args)
{
    const char *str;
    str = krb5_config_vget_string (context, c, args);
    if(str == NULL)
	return def_value;
    else {
	char *endptr;
	long l;
	l = strtol(str, &endptr, 0);
	if (endptr == str)
	    return def_value;
	else
	    return l;
    }
}
