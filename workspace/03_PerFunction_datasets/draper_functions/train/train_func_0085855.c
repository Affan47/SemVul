mprEscapeHtml(cchar *html)
{
    cchar   *ip;
    char    *result, *op;
    int     len;

    for (len = 1, ip = html; *ip; ip++, len++) {
        if (charMatch[(int) (uchar) *ip] & MPR_ENCODE_HTML) {
            len += 5;
        }
    }
    if ((result = mprAlloc(len)) == 0) {
        return 0;
    }


    op = result;
    while (*html != '\0') {
        if (charMatch[(uchar) *html] & MPR_ENCODE_HTML) {
            if (*html == '&') {
                strcpy(op, "&amp;");
                op += 5;
            } else if (*html == '<') {
                strcpy(op, "&lt;");
                op += 4;
            } else if (*html == '>') {
                strcpy(op, "&gt;");
                op += 4;
            } else if (*html == '#') {
                strcpy(op, "&#35;");
                op += 5;
            } else if (*html == '(') {
                strcpy(op, "&#40;");
                op += 5;
            } else if (*html == ')') {
                strcpy(op, "&#41;");
                op += 5;
            } else if (*html == '"') {
                strcpy(op, "&quot;");
                op += 6;
            } else if (*html == '\'') {
                strcpy(op, "&#39;");
                op += 5;
            } else {
                mprAssert(0);
            }
            html++;
        } else {
            *op++ = *html++;
        }
    }
    mprAssert(op < &result[len]);
    *op = '\0';
    return result;
}
