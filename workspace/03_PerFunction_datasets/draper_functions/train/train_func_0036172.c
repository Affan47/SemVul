drop_config(icons_priv *ics)
{
    wmpix_t *wp;

    ENTER;

    while (ics->wmpix)
    {
        wp = ics->wmpix;
        ics->wmpix = ics->wmpix->next;
        g_free(wp->ch.res_name);
        g_free(wp->ch.res_class);
        g_free(wp->data);
        g_free(wp);
    }


    if (ics->dicon)
    {
        g_free(ics->dicon->data);
        g_free(ics->dicon);
        ics->dicon = NULL;
    }


    g_hash_table_foreach_remove(ics->task_list,
        (GHRFunc) task_remove_every, (gpointer)ics);

    if (ics->wins)
    {
        DBG("free ics->wins\n");
        XFree(ics->wins);
        ics->wins = NULL;
    }
    RET();
}
