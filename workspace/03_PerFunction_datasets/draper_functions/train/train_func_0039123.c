vtag_comment_count(struct vtag *s, char const *key)
    {
    GSList *slist;
    struct valuestore vs = {0, 0};

    if (!(slist = slist_lookup(s, key)))
        return 0;

    g_slist_foreach(slist, slist_data_length, &vs);
    return vs.count;
    }
