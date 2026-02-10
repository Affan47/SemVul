Ns_ConfigGetInt(char *section, char *key, int *valuePtr)
{
    char           *s;

    s = Ns_ConfigGetValue(section, key);
    if (s == NULL || sscanf(s, "%d", valuePtr) != 1) {
        return NS_FALSE;
    }
    return NS_TRUE;
}
