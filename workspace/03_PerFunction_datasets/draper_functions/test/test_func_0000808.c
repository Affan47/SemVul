hmacmd5_do_hmac_internal(void *handle,
				     unsigned char const *blk, int len,
				     unsigned char const *blk2, int len2,
				     unsigned char *hmac)
{
    hmacmd5_start(handle);
    hmacmd5_bytes(handle, blk, len);
    if (blk2) hmacmd5_bytes(handle, blk2, len2);
    hmacmd5_genresult(handle, hmac);
}
