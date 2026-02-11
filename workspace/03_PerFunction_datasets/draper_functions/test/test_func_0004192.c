previewgui_set_pdffile (GuPreviewGui* pc, const gchar *uri) {

    previewgui_cleanup_fds (pc);

    pc->uri = g_strdup(uri);

    pc->doc = poppler_document_new_from_file (pc->uri, NULL, NULL);
    g_return_if_fail (pc->doc != NULL);

    pc->restore_x = -1;
    pc->restore_y = -1;

    load_document(pc, FALSE);


    synctex_clear_sync_nodes(pc);


    g_signal_handler_block(pc->combo_sizes, pc->combo_sizes_changed_handler);
    if (STR_EQU (config_get_value ("zoommode"), "pagewidth")) {
        set_fit_mode(pc, FIT_WIDTH);
        gtk_combo_box_set_active(pc->combo_sizes, ZOOM_FIT_WIDTH);
    } else if (STR_EQU (config_get_value ("zoommode"), "pageheight")) {
        set_fit_mode(pc, FIT_HEIGHT);

    } else if (STR_EQU (config_get_value ("zoommode"), "bestfit")) {
        set_fit_mode(pc, FIT_BOTH);
        gtk_combo_box_set_active(pc->combo_sizes, ZOOM_FIT_BOTH);
    } else {
        set_fit_mode(pc, FIT_NONE);
        previewgui_set_scale(pc, list_sizes[ZOOM_100],
                NAN,
                NAN);

        gtk_combo_box_set_active(pc->combo_sizes, ZOOM_100);
    }
    g_signal_handler_unblock(pc->combo_sizes, pc->combo_sizes_changed_handler);

    gtk_widget_queue_draw (pc->drawarea);

    previewgui_goto_page (pc, 0);
}
