dots2Slash(char *utf8) {
    char *pntr;

    for(pntr = utf8; *pntr != '\0'; pntr++)
        if(*pntr == '.')
            *pntr = '/';

    return utf8;
}
