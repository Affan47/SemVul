strdupn(const char *str, size_t n)
{
    char *out;
    size_t len;

    len = strlen(str);
    out = malloc(n*len+1);
    if (out != NULL) {
    	out[n*len] = '\0';
    	for (; n > 0; n--)
            memcpy(out+(n-1)*len, str, len);
    }

    return out;
}
