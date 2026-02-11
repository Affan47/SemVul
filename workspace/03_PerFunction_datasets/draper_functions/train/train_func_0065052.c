str_replace_all(char* buf, const char* s1, const char* s2) {
    char buf2[64000];
    while (1) {
        char* p = strstr(buf, s1);
        if (!p) break;
        strcpy(buf2, p+strlen(s1));
        strcpy(p, s2);
        strcat(p, buf2);
    }
}
