ginn_str2state(const char *str)
{
    if (str == NULL)
        return -1;
    if (strcmp(str, "start") == 0)
        return GINN_START;
    if (strcmp(str, "update") == 0)
        return GINN_UPDATE;
    if (strcmp(str, "finish") == 0)
        return GINN_FINISH;
    fprintf(stderr, "ERROR: Undefined state: %s\n", str);
    return -2;
}
