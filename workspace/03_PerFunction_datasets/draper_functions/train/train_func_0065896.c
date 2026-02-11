sgets(char* buf, int len, char*& in) {
    char* p;

    p = strstr(in, "\n");
    if (!p) return NULL;
    *p = 0;
    strlcpy(buf, in, len);
    *p = '\n';
    in = p+1;
    return buf;
}
