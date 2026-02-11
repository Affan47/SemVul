krb5_ret_int(krb5_storage *sp,
	     int32_t *value,
	     size_t len)
{
    int ret;
    unsigned char v[4];
    unsigned long w;
    ret = sp->fetch(sp, v, len);
    if (ret < 0)
	return errno;
    if ((size_t)ret != len)
	return sp->eof_code;
    _krb5_get_int(v, &w, len);
    *value = w;
    return 0;
}
