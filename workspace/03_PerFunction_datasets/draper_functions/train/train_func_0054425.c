scan_include(int terminator)
{
    static char buf[1024];
    int i = 0;
    while (1) {
        int c = input();
        if (c == terminator)
            break;
        else if (c == '\n') {
            yyerror("unterminated include filename");
            unput(c);
            break;
        } else if (i == 1023) {
            yyerror("include filename is too long");
            break;
        } else {
            buf[i++] = (char)c;
        }
    }
    buf[i] = '\0';
    LOCATION_STEP (yylloc);
    return buf;
}
