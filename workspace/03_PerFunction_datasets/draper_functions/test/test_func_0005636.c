on_page_input_changed (GtkEntry* entry, void* user) {


    gint newpage = atoi (gtk_entry_get_text (entry));
    newpage -= 1;
    newpage = MAX(newpage, 0);
    newpage = MIN(newpage, gui->previewgui->n_pages);

    if (STR_EQU (config_get_value ("animated_scroll"), "always")) {
        previewgui_scroll_to_page (gui->previewgui, newpage);
    } else {
        previewgui_goto_page (gui->previewgui, newpage);
    }

}
