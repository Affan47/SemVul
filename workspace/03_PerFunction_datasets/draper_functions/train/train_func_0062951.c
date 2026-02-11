_libssh2_store_str(unsigned char **buf, const char *str, size_t len)
{
    _libssh2_store_u32(buf, (uint32_t)len);
    if(len) {
        memcpy(*buf, str, len);
        *buf += len;
    }
}
