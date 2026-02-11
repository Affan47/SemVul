switch_page_cb(GtkNotebook *notebook, gpointer newpage, guint newpage_nth,
        gpointer user_data)
{
    GSList             *pos;
    HybridChatWindow   *chat;
    HybridBuddy        *buddy;
    GdkPixbuf          *pixbuf;
    HybridConversation *conv = (HybridConversation*)user_data;
    gint                page_index;

    for (pos = conv->chat_buddies; pos; pos = pos->next) {
        chat = (HybridChatWindow*)pos->data;

        page_index = gtk_notebook_page_num(GTK_NOTEBOOK(conv->notebook),
                chat->vbox);

        if (page_index == newpage_nth) {
            goto page_found;
        }
    }

    hybrid_debug_error("conv", "FATAL, can not find an exist buddy\n");

    return;

page_found:

    if (IS_SYSTEM_CHAT(chat)) {

        buddy = chat->data;


        pixbuf = hybrid_create_pixbuf(buddy->icon_data, buddy->icon_data_length);
        gtk_window_set_icon(GTK_WINDOW(conv->window), pixbuf);
        g_object_unref(pixbuf);


        gtk_window_set_title(GTK_WINDOW(conv->window),
            (!buddy->name || *(buddy->name) == '\0') ? buddy->id : buddy->name);
    }
}
