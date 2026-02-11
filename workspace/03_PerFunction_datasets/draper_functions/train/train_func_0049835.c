md5_wrapper(const unsigned char *data, size_t len, char *md5)
{
        unsigned short i = 0;
        unsigned short lim = MD5_DIGEST_LENGTH*2+1;
        unsigned char scratch[MD5_DIGEST_LENGTH] = {0,};
        MD5(data, len, scratch);
        for (; i < MD5_DIGEST_LENGTH; i++)
                snprintf(md5 + i * 2, lim-i*2, "%02x", scratch[i]);
}
