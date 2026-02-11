quotedString(const UChar *string) {
    int len = u_strlen(string);
    int alen = len;
    const UChar *sp;
    UChar *newstr, *np;

    for (sp = string; *sp; ++sp) {
        switch (*sp) {
            case '\n':
            case 0x0022:
                ++alen;
                break;
        }
    }

    newstr = (UChar *) uprv_malloc((1 + alen) * sizeof(*newstr));
    for (sp = string, np = newstr; *sp; ++sp) {
        switch (*sp) {
            case '\n':
                *np++ = 0x005C;
                *np++ = 0x006E;
                break;

            case 0x0022:
                *np++ = 0x005C;

            default:
                *np++ = *sp;
                break;
        }
    }
    *np = 0;

    return newstr;
}
