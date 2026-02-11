FixSlashes(const plString& src) {
    if (src.empty())
        return plString();

    char* pbuf = strdup(src);
    for (char* pc = pbuf; *pc != 0; pc++) {
        if (*pc == '/' || *pc == '\\')
            *pc = PATHSEP;
    }
    plString dest(pbuf);
    free(pbuf);
    return dest;
}
