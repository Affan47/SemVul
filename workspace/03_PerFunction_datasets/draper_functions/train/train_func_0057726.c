scanner_pending_add(scanner_pending_t *pending, const GArray *restrictions, const char *path)
{
    GList *n, *nlast;

    for (n = pending->paths; n != NULL; n = n->next) {
        const char *other = n->data;
        if (g_str_has_prefix(path, other)) {
            g_debug("Path already in pending scan in category %s: %s (%s)",
                    pending->category, path, other);
            return;
        }
    }


    if (restrictions && (!scanner_category_allows_path(restrictions, path))) {
        g_warning("Path is outside of category %s directories: %s",
                  pending->category, path);
        return;
    }

    nlast = NULL;
    for (n = pending->paths; n != NULL; ) {
        char *other = n->data;

        nlast = n;

        if (!g_str_has_prefix(other, path))
            n = n->next;
        else {
            GList *tmp;

            g_debug("Path covers previous pending scan in category %s, "
                    "replace %s (%s)",
                    pending->category, other, path);

            tmp = n->next;
            nlast = n->next ? n->next : n->prev;

            pending->paths = g_list_delete_link(pending->paths, n);
            g_free(other);

            n = tmp;
        }
    }

    g_debug("New scan path for category %s: %s", pending->category, path);


    n = g_list_alloc();
    n->data = g_strdup(path);
    n->next = NULL;
    n->prev = nlast;

    if (nlast)
        nlast->next = n;
    else
        pending->paths = n;
}
