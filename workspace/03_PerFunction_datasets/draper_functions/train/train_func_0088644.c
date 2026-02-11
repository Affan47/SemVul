krb5_kt_store_keyblock(krb5_context context,
		       struct fkt_data *fkt,
		       krb5_storage *sp,
		       krb5_keyblock *p)
{
    int ret;

    ret = krb5_store_int16(sp, p->keytype);
    if(ret) {
	krb5_set_error_message(context, ret,
			       N_("Cant store keyblock to file %s", ""),
			       fkt->filename);
	return ret;
    }
    ret = krb5_kt_store_data(context, sp, p->keyvalue);
    if (ret)
	krb5_set_error_message(context, ret,
			       N_("Cant store keyblock to file %s", ""),
			       fkt->filename);
    return ret;
}
