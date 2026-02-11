fm_mime_type_get_thumbnailers_list(FmMimeType* mime_type)
{
    GList *list = NULL, *l;

    G_LOCK(thumbnailers);
    for (l = mime_type->thumbnailers; l; l = l->next)
        list = g_list_prepend(list, fm_thumbnailer_ref(l->data));
    list = g_list_reverse(list);
    G_UNLOCK(thumbnailers);
    return list;
}
