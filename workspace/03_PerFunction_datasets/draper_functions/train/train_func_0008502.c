splitFields(const char* line, char* fields[], int maxFields, char splitChar)
{
    const char *p;
    int foundFields = 0;
    int len;

    do {
#ifdef __BORLANDC__

        p = strchr(OFconst_cast(char *, line), splitChar);
#else
        p = strchr(line, splitChar);
#endif
        if (p == NULL) {
            len = strlen(line);
        } else {
            len = p - line;
        }
        fields[foundFields] = OFstatic_cast(char *, malloc(len + 1));
        strncpy(fields[foundFields], line, len);
        fields[foundFields][len] = '\0';
        foundFields++;
        line = p + 1;
    } while ((foundFields < maxFields) && (p != NULL));

    return foundFields;
}
