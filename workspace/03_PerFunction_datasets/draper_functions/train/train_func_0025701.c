bname_is_temp (const char *name)
{
    return !strncmp(name, "btmp___", 7) && isdigit(name[7]);
}
