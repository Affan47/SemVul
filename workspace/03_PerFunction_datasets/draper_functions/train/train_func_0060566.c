htmldecode(src, dst)
    STR src, dst; {

    pchar ch1, ch2, ch3;
    int p;
    TOKEN token;
    int i;

    ch1 = src;
    ch2 = dst;

    while (*ch1) {
        if (*ch1 != '&')
            *ch2++ = *ch1++;
        else {
            ch3 = token;
            ch1++;
            while (*ch1 && *ch1 != ';') *ch3++ = *ch1++;
            if (*ch1) ch1++;
            *ch3 = '\0';
            if (token[0] == '#') {
                ch3 = token + 1;
                p = atoi(ch3);
                *ch2++ = (char)p;
            } else {
                p = 1;
                i = 0;
                while (p && html2char[i].c) {
                    if (!strncasecmp(token, html2char[i].h,
                           strlen(token))) {
                               *ch2++ = html2char[i].c;
                               p = 0;
                    }
                    i++;
                }
                if (p) {
                    *ch2++ = '&';
                    ch3 = token;
                    while (*ch3) *ch2++ = *ch3++;
                }
            }
        }
    }
    *ch2 = '\0';
}
