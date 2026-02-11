find_treasurelist(const char *name) {
    const char *tmp = find_string(name);
    treasurelist *tl;


    if (!strcmp(name, "none") || (!first_treasurelist))
        return NULL;
    if (tmp != NULL)
        for (tl = first_treasurelist; tl != NULL; tl = tl->next)
            if (tmp == tl->name)
                return tl;
    LOG(llevError, "Couldn't find treasurelist %s\n", name);
    return NULL;
}
