getline() {
    char linebuf[BUFSIZE];
    int l = 0, eol = 0, left = 0, right = 0;
    if (bufsiz == -1) return NULL;
    while (l < bufsiz && !eol) {
        linebuf[l++] = out[outc];
        switch (out[outc]) {
            case '\t': break;
            case 31: {
                if (++outc == bufsiz) {
                    bufsiz = getbuf();
                    outc = 0;
                }
                linebuf[l - 1] = out[outc];
                break;
            }
            case ' ': break;
            default: if (((unsigned char) out[outc]) < 47) {
                if (out[outc] > 32) {
                    right = out[outc] - 31;
                    if (++outc == bufsiz) {
                        bufsiz = getbuf();
                        outc = 0;
                    }
                }
                if (out[outc] == 30) left = 9; else left = out[outc];
                linebuf[l-1] = '\n';
                eol = 1;
            }
        }
        if (++outc == bufsiz) {
            outc = 0;
            bufsiz = fin ? getbuf(): -1;
        }
    }
    if (right) strcpy(linebuf + l - 1, line + strlen(line) - right - 1);
    else linebuf[l] = '\0';
    strcpy(line + left, linebuf);
    return line;
}
