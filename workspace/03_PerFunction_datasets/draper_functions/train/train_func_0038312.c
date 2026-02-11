rsvg_defs_free_toresolve (RsvgDefs *defs)
{
    GSList *l;

    for (l = defs->toresolve; l ; l = l ->next) {
        RsvgResolutionPending *data = l->data;

        g_free (data->name);
        g_free (data);
    }
    g_slist_free (defs->toresolve);
}
