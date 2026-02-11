simple_fname (char *dest, const char *src)
{
    char *p;
    const char *s;

    s = strrchr(src, SLASH);


    if (s != NULL) {
        strcpy(dest, s + 1);
    } else {
        strcpy(dest, src);
    }


    p = strrchr(dest, '.');
    if (p != NULL && strlen(dest) > 3) {
	*p = '\0';
    }

    return dest;
}
