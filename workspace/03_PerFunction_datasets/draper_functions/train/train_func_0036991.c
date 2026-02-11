strcpy_s(char* dst, size_t dst_size, const char* src)
{
    size_t src_size = strlen(src) + 1;
    if (src_size <= dst_size)
        memcpy(dst, src, src_size);
    else {
        if (dst_size > 0) {
            memcpy(dst, src, dst_size);
            dst[dst_size-1] = 0;
        }
    }
}
