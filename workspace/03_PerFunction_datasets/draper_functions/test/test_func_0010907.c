CheckSignatures(deh_context_t *context)
{
    size_t i;
    char *line;


    line = DEH_ReadLine(context);

    if (line == NULL)
    {
        return false;
    }


    for (i=0; deh_signatures[i] != NULL; ++i)
    {
        if (!strcmp(deh_signatures[i], line))
        {
            return true;
        }
    }

    return false;
}
