ClearFileFromPrivate()
{
        for (GSList *tlist = prlist; tlist; tlist = g_slist_next(tlist))
                delete (FileInfo *)tlist->data;
        g_slist_free(prlist);
        prlist = NULL;
}
