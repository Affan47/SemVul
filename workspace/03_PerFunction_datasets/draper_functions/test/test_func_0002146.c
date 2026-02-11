qfits_getcomment_r(const char* line, char* comment) {
    int    i;
    int    from, to;
    int    inq;

    if (line==NULL) {
#ifdef DEBUG_FITSHEADER
        printf("qfits_getcomment: null line in input\n");
#endif
        return NULL;
    }


    if (!strncmp(line, "END ", 4)) return NULL;
    if (!strncmp(line, "HISTORY ", 8)) return NULL;
    if (!strncmp(line, "COMMENT ", 8)) return NULL;
    if (!strncmp(line, "        ", 8)) return NULL;

    memset(comment, 0, 81);

    i=0;
    while (line[i]!='=' && i<80) i++;
    if (i>=80) {
#ifdef DEBUG_FITSHEADER
        printf("qfits_getcomment: no equal sign on line\n");
#endif
        return NULL;
    }
    i++;


    inq = 0;
    while (i<80) {
        if (line[i]=='\'')
            inq = !inq;
        if (line[i]=='/')
            if (!inq)
                break;
        i++;
    }
    if (i>=80) {
#ifdef DEBUG_FITSHEADER
        printf("qfits_getcomment: no slash found on line\n");
#endif
        return NULL;
    }
    i++;

    while (line[i]==' ') i++;
    from=i;


    to=79;
    while (line[to]==' ') to--;

    if (to<from) {
#ifdef DEBUG_FITSHEADER
        printf("qfits_getcomment: from>to?\n");
#endif
        return NULL;
    }

    strncpy(comment, line+from, to-from+1);

    comment[to-from+1] = '\0';
    return comment;
}
