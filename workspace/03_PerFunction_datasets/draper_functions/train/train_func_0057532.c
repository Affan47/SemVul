ExpandTilde (const char* tildeName, int length) {
    const char* name = nil;

    if (length > 1) {
        static char buf[MAX_PATH_LENGTH+1];
        strncpy(buf, tildeName+1, length-1);
        buf[length-1] = '\0';
        name = buf;
    }
    return Home(name);
}
