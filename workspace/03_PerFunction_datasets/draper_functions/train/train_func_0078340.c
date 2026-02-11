_xdg_mime_alias_read_from_file(XdgAliasList *list,
                               const char   *file_name)
{
    FILE *file;
    char line[255];
    int alloc;


    file = fopen(file_name, "r");

    if (file == NULL)
        return;


    alloc = list->n_aliases + 16;
    list->aliases = (XdgAlias *)realloc(list->aliases, alloc * sizeof(XdgAlias));
    while (fgets(line, 255, file) != NULL)
    {
        char *sep;
        if (line[0] == '#')
            continue;

        sep = strchr(line, ' ');
        if (sep == NULL)
            continue;
        *(sep++) = '\000';
        sep[strlen(sep) -1] = '\000';
        if (list->n_aliases == alloc)
        {
            alloc <<= 1;
            list->aliases = (XdgAlias *)realloc(list->aliases,
                                                alloc * sizeof(XdgAlias));
        }
        list->aliases[list->n_aliases].alias = strdup(line);
        list->aliases[list->n_aliases].mime_type = strdup(sep);
        list->n_aliases++;
    }
    list->aliases = (XdgAlias *)realloc(list->aliases,
                                        list->n_aliases * sizeof(XdgAlias));

    fclose(file);

    if (list->n_aliases > 1)
        qsort(list->aliases, list->n_aliases,
              sizeof(XdgAlias), alias_entry_cmp);
}
