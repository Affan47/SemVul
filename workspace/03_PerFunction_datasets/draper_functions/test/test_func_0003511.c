nstrndup(const char *s1, int l) {
    if (! s1 || l == 0) return (char *) 0;

    char *s2 = new char[l+1];
    strncpy(s2, s1, l);
    s2[l] = '\0';
    return s2;
}
