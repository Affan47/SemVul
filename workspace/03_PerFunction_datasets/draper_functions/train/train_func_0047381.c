an(const char *str)
{
    char *buf = nextobuf();

    buf[0] = '\0';

    if (strncmpi(str, "the ", 4) &&
        strcmp(str, "molten lava") &&
        strcmp(str, "iron bars") &&
        strcmp(str, "ice"))
    {
        if (index(vowels, *str) &&
            strncmp(str, "one-", 4) &&
            strncmp(str, "useful", 6) &&
            strncmp(str, "unicorn", 7) &&
            strncmp(str, "uranium", 7) &&
            strncmp(str, "eucalyptus", 10))
        {
            strcpy(buf, "an ");
        }
        else
        {
            strcpy(buf, "a ");
        }
    }

    strcat(buf, str);
    return buf;
}
