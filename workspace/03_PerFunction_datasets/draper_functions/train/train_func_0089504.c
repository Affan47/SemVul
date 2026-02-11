maybe_add_object (SeahorseSet *skset, SeahorseObject *sobj)
{
    if (seahorse_object_get_context (sobj) != SCTX_APP ())
        return FALSE;

    if (g_hash_table_lookup (skset->pv->objects, sobj))
        return FALSE;

    if (!skset->pv->pred || !seahorse_object_predicate_match (skset->pv->pred, sobj))
        return FALSE;

    g_hash_table_replace (skset->pv->objects, sobj, GINT_TO_POINTER (TRUE));
    g_signal_emit (skset, signals[ADDED], 0, sobj);
    g_signal_emit (skset, signals[SET_CHANGED], 0);
    return TRUE;
}
