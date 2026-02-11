SetHHEVersionByName(char *name)
{
    int i;

    for (i=0; i<arrlen(hhe_versions); ++i)
    {
        if (!strcmp(hhe_versions[i], name))
        {
            deh_hhe_version = i;
            return;
        }
    }

    fprintf(stderr, "Unknown Heretic version: %s\n", name);
    fprintf(stderr, "Valid versions:\n");

    for (i=0; i<arrlen(hhe_versions); ++i)
    {
        fprintf(stderr, "\t%s\n", hhe_versions[i]);
    }
}
