url_escape(const char *src)
{
    int len = strlen(src);
    unsigned char *decoded;
    int i;
    char *dst;
    int done = 0;

    decoded = calloc(1, len + 1);

    dst = (char *)decoded;

    for(i=0; i < len; i++) {
        switch(src[i]) {
        case '%':
            if(i+2 >= len) {
                free(decoded);
                return NULL;
            }
            if(hex(src[i+1]) == -1 || hex(src[i+2]) == -1 ) {
                free(decoded);
                return NULL;
            }

            *dst++ = hex(src[i+1]) * 16  + hex(src[i+2]);
            i+= 2;
            break;
        case '+':
            *dst++ = ' ';
            break;
        case '#':
            done = 1;
            break;
        case 0:
            free(decoded);
            return NULL;
            break;
        default:
            *dst++ = src[i];
            break;
        }
        if(done)
            break;
    }

    *dst = 0;

    return (char *)decoded;
}
