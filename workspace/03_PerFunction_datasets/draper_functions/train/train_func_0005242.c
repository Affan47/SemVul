krb5_kt_get_full_name(krb5_context context,
		      krb5_keytab keytab,
		      char **str)
{
    char type[KRB5_KT_PREFIX_MAX_LEN];
    char name[MAXPATHLEN];
    krb5_error_code ret;

    *str = NULL;

    ret = krb5_kt_get_type(context, keytab, type, sizeof(type));
    if (ret)
	return ret;

    ret = krb5_kt_get_name(context, keytab, name, sizeof(name));
    if (ret)
	return ret;

    if (asprintf(str, "%s:%s", type, name) == -1) {
	*str = NULL;
	return krb5_enomem(context);
    }

    return 0;
}
