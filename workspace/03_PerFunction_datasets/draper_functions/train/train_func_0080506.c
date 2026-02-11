strpcpyf(char **dest, size_t size, const char *src, ...)
{
        va_list va;
        int i;

        va_start(va, src);
        i = vsnprintf(*dest, size, src, va);
        if (i < (int)size) {
                *dest += i;
                size -= i;
        } else {
                *dest += size;
                size = 0;
        }
        va_end(va);
        *dest[0] = '\0';
        return size;
}
