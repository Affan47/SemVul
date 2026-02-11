editor_redo_change (GuEditor* ec) {
    GtkTextIter current;
    if (gtk_source_buffer_can_redo (ec->buffer)) {
        gtk_source_buffer_redo (ec->buffer);
        editor_get_current_iter (ec, &current);
        editor_scroll_to_cursor (ec);
        gtk_text_buffer_set_modified (ec_buffer, TRUE);
    }
}
