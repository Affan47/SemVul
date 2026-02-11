hybrid_conv_got_input(HybridAccount *account, const gchar *buddy_id, gboolean auto_stop)
{
    HybridBuddy      *buddy;
    HybridChatWindow *chat;
    gchar            *text;

    g_return_if_fail(account != NULL);
    g_return_if_fail(buddy_id != NULL);

    if (!(buddy = hybrid_blist_find_buddy(account, buddy_id))) {

        hybrid_debug_error("conv", "buddy doesn't exist.");
        return;
    }

    if (!(chat = hybrid_conv_find_chat(buddy_id))) {
        return;
    }

    text = g_strdup_printf(_(" %s is typing..."), buddy->name);

    text_ops->notify(chat->textview, text , MSG_NOTIFICATION_INPUT);

    g_free(text);

    if (!auto_stop) {
        return;
    }

    if (chat->input_source) {
        g_source_remove(chat->input_source);
    }

    chat->input_source =
        g_timeout_add_seconds(4, (GSourceFunc)(input_finished_cb), chat);
}
