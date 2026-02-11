confirm_remove_current(void)
{
    gchar *filename, *msg;

    if (current_image == NULL || current_image->node == NULL)
        return FALSE;

    filename = current_image->node->data;
    msg = g_strdup_printf(_("Do you really want to delete this file?\n%s\n"),
                          filename_to_utf8(filename));

    if (show_remove_dialog(msg)) {
        add_obsolete_node(current_image->node);

        if (remove(filename) < 0)
            perror(filename);
    }

    g_free(msg);
    return FALSE;
}
