snippets_load (GuSnippets* sc) {
    FILE* fh = 0;
    gchar buf[BUFSIZ];
    gchar* rot = NULL;
    gchar* seg = NULL;
    slist* current = NULL;
    slist* prev = NULL;

    if (sc->head)
        snippets_clean_up (sc);

    if (! (fh = fopen (sc->filename, "r"))) {
        slog (L_ERROR, "can't find snippets file, reseting to default\n");
        snippets_set_default (sc);
        return;
    }

    while (fgets (buf, BUFSIZ, fh)) {
        current = g_new0 (slist, 1);
        if (!sc->head)
            sc->head = prev = current;
        prev->next = current;
        buf[strlen (buf) -1] = 0;

        if (buf[0] != '\t') {
            if ('#' == buf[0] || !strlen(buf)) {
                current->first = g_strdup (buf);
            } else {
                seg = strstr (buf, " ") + 1;
                current->first = g_strdup ((seg == buf)? "Invalid": seg);
                snippets_set_accelerator (sc, current->first);
            }
        } else {
            if (!prev->second) {
                prev->second = g_strdup (buf + 1);
                continue;
            }
            rot = g_strdup (prev->second);
            g_free (prev->second);
            prev->second = g_strconcat (rot, "\n", buf + 1, NULL);
            g_free (rot);
            g_free (current);
            current = prev;
        }
        prev = current;
    }
    if (prev) prev->next = NULL;
    fclose (fh);
}
