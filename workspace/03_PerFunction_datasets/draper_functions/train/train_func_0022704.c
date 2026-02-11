taxtable_entries_handler (xmlNodePtr node, gpointer taxtable_pdata)
{
    struct taxtable_pdata *pdata = taxtable_pdata;
    xmlNodePtr mark;

    g_return_val_if_fail (node, FALSE);
    g_return_val_if_fail (node->xmlChildrenNode, FALSE);

    for (mark = node->xmlChildrenNode; mark; mark = mark->next)
    {
        GncTaxTableEntry *entry;

        if (g_strcmp0 ("text", (char*)mark->name) == 0)
            continue;

        if (g_strcmp0 (gnc_taxtableentry_string, (char*)mark->name))
            return FALSE;

        entry = dom_tree_to_ttentry (mark, pdata->book);

        if (entry)
            gncTaxTableAddEntry (pdata->table, entry);
        else
            return FALSE;

    }
    return TRUE;
}
