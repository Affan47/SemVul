_xdg_mime_alias_list_lookup(XdgAliasList *list,
                            const char   *alias)
{
    XdgAlias *entry;
    XdgAlias key;

    if (list->n_aliases > 0)
    {
        key.alias = (char *)alias;
        key.mime_type = 0;

        entry = (XdgAlias *)bsearch(&key, list->aliases, list->n_aliases,
                                    sizeof(XdgAlias), alias_entry_cmp);
        if (entry)
            return entry->mime_type;
    }

    return NULL;
}
