serialize_collection_nogui(const gchar * filename)
{
    FILE *tty;
    FILE *file;
    gint res;
    gboolean cancel = FALSE;

    if (get_list_head() == NULL) {
        g_printerr(_("No images to put in a collection\n"));
        return 1;
    }

    if (filename == NULL) {
        file = stdout;
        if (isatty(fileno(file))) {
            g_printerr(_("GLiv won't write a collection to a terminal\n"));
            return 1;
        }
    } else {

        remove(filename);

        file = fopen(filename, "w");
        if (file == NULL) {
            perror(filename);
            return 1;
        }
    }

    tty = get_terminal_output();
    if (tty != NULL) {
        fprintf(tty, _("Saving collection: %s"), filename_to_utf8(filename));
        putc('\n', tty);
    }

    res = save_collection(file, &cancel);

    if (res)
        perror(filename == NULL ? _("Standard output") : filename);

    if (filename != NULL && fclose(file) < 0 && res == 0)
        perror(filename);

    return res;
}
