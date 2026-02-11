strcat_s(char *dst, size_t dst_size, const char* src)
{
    size_t dst_len = strlen(dst);
    if (dst_len >= dst_size) {
        if (dst_size > 0)
            dst[dst_size-1] = 0;
        return;
    }
    strcpy_s(dst+dst_len, dst_size - dst_len, src);
}
