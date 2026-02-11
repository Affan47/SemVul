hybrid_chat_textview_notify(GtkWidget *textview, const gchar *text, gint type)
{
    GtkTextBuffer *recv_tb;
    GtkTextIter end_iter;
    GtkTextIter stop_iter;
    GtkTextIter start_iter;
    GtkTextMark *mark;

    recv_tb  = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    gtk_text_buffer_get_end_iter(recv_tb, &end_iter);

    gtk_text_view_backward_display_line(GTK_TEXT_VIEW(textview), &end_iter);

    gtk_text_buffer_get_end_iter(recv_tb, &stop_iter);
    gtk_text_buffer_get_start_iter(recv_tb, &start_iter);


    if (gtk_text_iter_equal(&end_iter, &stop_iter)) {
        gtk_text_buffer_delete(recv_tb, &start_iter, &stop_iter);

    } else {
        gtk_text_buffer_delete(recv_tb, &end_iter, &stop_iter);

        if (!gtk_text_iter_equal(&start_iter, &end_iter)) {
            gtk_text_buffer_insert(recv_tb, &end_iter, "\n", -1);
        }
    }

    gtk_text_buffer_get_end_iter(recv_tb, &end_iter);

    if (type == MSG_NOTIFICATION_INPUT) {
        gtk_text_buffer_insert_with_tags_by_name(recv_tb, &end_iter,
                        text, strlen(text), "grey", "small", "wrap", NULL);
    }

    mark = gtk_text_buffer_get_mark(recv_tb, "scroll");
    gtk_text_buffer_move_mark(recv_tb, mark, &end_iter);
    gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(textview), mark);
}
