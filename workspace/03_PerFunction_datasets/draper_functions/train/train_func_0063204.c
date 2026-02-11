readHeader(FILE *f, int & version)
{
    char line[MAX_MACRO_LINE];
    if (!fgets(line, sizeof(line), f)) {
        if (feof(f)) {
            fseek(f, 0, SEEK_SET);
            version = 0;
            return true;
        }
        return false;
    }


    char *p = line;
    size_t len = strlen(line);
    if (len >= 3 && (unsigned char)line[0] == 0xEF && (unsigned char)line[1] == 0xBB &&
                    (unsigned char)line[2] == 0xBF)
    {
        p += 3;
    }


    p = strstr(p, "***");
    if (p) {
        p += 3;

        while (*p == ' ') p++;
        if (sscanf(p, "version=%d", &version) == 1)
            return true;
    }

    fseek(f, 0, SEEK_SET);
    version = 0;
    return true;
}
