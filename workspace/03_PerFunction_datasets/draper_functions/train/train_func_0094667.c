store_gss_init_res(krb5_storage *sp, krb5_data handle,
		   OM_uint32 maj_stat, OM_uint32 min_stat,
		   uint32_t seq_window, gss_buffer_t gout)
{
    krb5_error_code ret;
    krb5_data out;

    out.data = gout->value;
    out.length = gout->length;

    ret = store_data_xdr(sp, handle);
    if (ret) return ret;
    ret = krb5_store_uint32(sp, maj_stat);
    if (ret) return ret;
    ret = krb5_store_uint32(sp, min_stat);
    if (ret) return ret;
    ret = store_data_xdr(sp, out);
    return ret;
}
