any_add_entry(krb5_context context,
	      krb5_keytab id,
	      krb5_keytab_entry *entry)
{
    struct any_data *a = id->data;
    krb5_error_code ret;
    while(a != NULL) {
	ret = krb5_kt_add_entry(context, a->kt, entry);
	if(ret != 0 && ret != KRB5_KT_NOWRITE) {
	    krb5_set_error_message(context, ret,
				   N_("failed to add entry to %s", ""),
				   a->name);
	    return ret;
	}
	a = a->next;
    }
    return 0;
}
