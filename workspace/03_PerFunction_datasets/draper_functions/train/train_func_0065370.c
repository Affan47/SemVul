free_lang_list (GList *list)
{
    GList *l = list;
    while (l) {
        g_free (l->data);
        l->data = NULL;
        l = l->next;
    }
    g_list_free (list);
}
