fwrite_crypt(buf, ptr, len, fp)
    buf_T	*buf UNUSED;
    char_u	*ptr;
    size_t	len;
    FILE	*fp;
{
#ifdef FEAT_CRYPT
    char_u  *copy;
    char_u  small_buf[100];
    size_t  i;

    if (*buf->b_p_key == NUL)
	return fwrite(ptr, len, (size_t)1, fp);
    if (len < 100)
	copy = small_buf;
    else
    {
	copy = lalloc(len, FALSE);
	if (copy == NULL)
	    return 0;
    }
    crypt_encode(ptr, len, copy);
    i = fwrite(copy, len, (size_t)1, fp);
    if (copy != small_buf)
	vim_free(copy);
    return i;
#else
    return fwrite(ptr, len, (size_t)1, fp);
#endif
}
