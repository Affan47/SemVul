isck(char *name)
{
    if (!name || !CK)
        return 0;
    else
        if (!strcmp(name, CK))
            return 1;
        else
            return 0;
}
