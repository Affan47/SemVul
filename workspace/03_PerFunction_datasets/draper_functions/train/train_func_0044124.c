fkt_setup_keytab(krb5_context context,
		 krb5_keytab id,
		 krb5_storage *sp)
{
    krb5_error_code ret;
    ret = krb5_store_int8(sp, 5);
    if(ret)
	return ret;
    if(id->version == 0)
	id->version = KRB5_KT_VNO;
    return krb5_store_int8 (sp, id->version);
}
