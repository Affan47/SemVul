compare(const char* a, int a_len, const char* b, int b_len)
{
    if (a != b) {
        int len = a_len < b_len ? a_len : b_len;
        int cmp = memcmp(a, b, len);
        if (cmp != 0)
            return cmp;
    }
    return a_len - b_len;
}
