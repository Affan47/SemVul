krb5_store_int(krb5_storage *sp,
	       int32_t value,
	       size_t len)
{
    int ret;
    unsigned char v[16];

    if(len > sizeof(v))
	return EINVAL;
    _krb5_put_int(v, value, len);
    ret = sp->store(sp, v, len);
    if (ret < 0)
	return errno;
    if ((size_t)ret != len)
	return sp->eof_code;
    return 0;
}
