storeKeyText(const unsigned char *key)
{
    static MemBuf mb = MemBufNULL;
    int i;
    memBufReset(&mb);
    for (i = 0; i < SQUID_MD5_DIGEST_LENGTH; i++)
	memBufPrintf(&mb, "%02X", *(key + i));
    return mb.buf;
}
