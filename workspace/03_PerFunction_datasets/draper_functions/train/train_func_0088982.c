seahorse_operation_list_free (GSList *list)
{
    GSList *l;

    for (l = list; l; l = g_slist_next (l)) {
        g_assert (SEAHORSE_IS_OPERATION (l->data));
        g_object_unref (G_OBJECT (l->data));
    }

    g_slist_free (list);
    return NULL;
}
