get_check_entry(const char *name, kadm5_principal_ent_rec *ent)
{
    krb5_error_code ret;
    krb5_principal principal;

    ret = krb5_parse_name(context, name, &principal);
    if (ret) {
	krb5_warn(context, ret, "krb5_unparse_name: %s", name);
	return 1;
    }

    memset(ent, 0, sizeof(*ent));
    ret = kadm5_get_principal(kadm_handle, principal, ent, KADM5_ATTRIBUTES);
    krb5_free_principal(context, principal);
    if(ret)
	return 1;

    return 0;
}
