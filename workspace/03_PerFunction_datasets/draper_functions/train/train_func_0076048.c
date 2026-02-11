json_principal(krb5_context context, krb5_principal princ,
               k5_json_value *val_out)
{
    krb5_error_code ret;
    k5_json_string str = NULL;
    char *princname;

    *val_out = NULL;
    if (princ == NULL)
        return k5_json_null_create_val(val_out);
    ret = krb5_unparse_name(context, princ, &princname);
    if (ret)
        return ret;
    ret = k5_json_string_create(princname, &str);
    krb5_free_unparsed_name(context, princname);
    *val_out = str;
    return ret;
}
