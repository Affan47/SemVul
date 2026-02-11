harmony_get_device_pin_callback(LmMessageHandler* handler, LmConnection *connection, LmMessage *message, gpointer void_harmony) {
    char *pin;
    MP3tunesHarmony *harmony = MP3TUNES_HARMONY(void_harmony);
    LmMessageNode *harmony_pin_node;

    (void)handler;
    (void)connection;

    harmony_pin_node = lm_message_node_get_child(message->node, "pin");
    if (harmony_pin_node) {
        pin = g_strdup(lm_message_node_get_value(harmony_pin_node));
        mp3tunes_harmony_set_pin(harmony, pin);
        g_free(pin);
        close_connection(harmony);
        open_connection(harmony);
        return LM_HANDLER_RESULT_REMOVE_MESSAGE;
    }
    return LM_HANDLER_RESULT_ALLOW_MORE_HANDLERS;
}
