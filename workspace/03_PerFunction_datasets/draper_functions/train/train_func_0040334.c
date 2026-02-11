scanner_pending_get_or_add(scanner_t *scanner, const char *category)
{
    scanner_pending_t *pending;
    GList *n, *nlast = NULL;

    g_assert(scanner->thread == NULL);

    for (n = scanner->pending_scan; n != NULL; n = n->next) {
        nlast = n;
        pending = n->data;
        if (strcmp(pending->category, category) == 0)
            return pending;
    }

    pending = g_new0(scanner_pending_t, 1);
    pending->category = g_strdup(category);
    pending->paths = NULL;


    n = g_list_alloc();
    n->data = pending;
    n->next = NULL;
    n->prev = nlast;

    if (nlast)
        nlast->next = n;
    else
        scanner->pending_scan = n;

    return pending;
}
