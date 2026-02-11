FOPEN(filename, mode)
    STR filename, mode; {
    FILE *f;

    f = fopen(filename, mode);
    if (f) return f;
#ifndef __DEBUG__
    printf("Content-type: text/plain\n\n");
#endif
    printf("Could not open %s", filename);
    if (strchr(mode, 'w')) printf(" for write"); else
    if (strchr(mode, 'r')) printf(" for read");
#ifndef _WIN32
    printf(": %s%s", sys_errlist[errno], NEWLINE);
#endif
    printf(NEWLINE);
    exit(0);
}
