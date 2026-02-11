jk_canonenc(const char *x, char *y, int maxlen)
{
    int i, j;
    int ch = x[0];
    char *allowed;
    char *reserved;


    allowed = "~$-_.+!*'(),;:@&=";
    reserved = "/";

    for (i = 0, j = 0; ch != '\0' && j < maxlen; i++, j++, ch=x[i]) {

        if (strchr(reserved, ch)) {
            y[j] = ch;
            continue;
        }

        if (!jk_isalnum(ch) && !strchr(allowed, ch)) {
            if (j+2<maxlen) {
                jk_c2hex(ch, &y[j]);
                j += 2;
            }
            else {
                return JK_FALSE;
            }
        }
        else {
            y[j] = ch;
        }
    }
    if (j<maxlen) {
        y[j] = '\0';
        return JK_TRUE;
    }
    else {
        return JK_FALSE;
    }
}
