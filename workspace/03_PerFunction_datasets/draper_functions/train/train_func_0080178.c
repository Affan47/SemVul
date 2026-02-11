dumpString(const char *s) {
    fputc('"', stdout);
    while (*s) {
        int c = *s++;
        switch (c) {
        case '\b':
            fprintf(stdout, "\\b");
            break;
        case '\f':
            fprintf(stdout, "\\f");
            break;
        case '\n':
            fprintf(stdout, "\\n");
            break;
        case '\r':
            fprintf(stdout, "\\r");
            break;
        case '\t':
            fprintf(stdout, "\\t");
            break;
        case '\\':
            fprintf(stdout, "\\\\");
            break;
        case '"':
            fprintf(stdout, "\\\"");
            break;
        default:
            fputc(c, stdout);
        }
    }
    fprintf(stdout, "%s\"", s);
}
