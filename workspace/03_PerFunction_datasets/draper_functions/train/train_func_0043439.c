bus_test_client_send_key (BusTestClient *client,
                     guint      keysym)
{
    gboolean is_modifier = _is_modifier_key (keysym);
    gint16 keycode;
    guint state;

    if (is_modifier) {
        IDEBUG ("key: %d is modifier.", keysym);
        gboolean is_modifier_set = _is_modifier_set (client, keysym);
        keycode = _get_keysym_to_keycode (keysym);
        state = _get_modifiers_to_mask (client);

        if (is_modifier_set) {
            state |= IBUS_RELEASE_MASK;
        }
        ibus_input_context_process_key_event (client->ibuscontext,
                                              keysym,
                                              keycode,
                                              state);
        _store_modifier_state (client, keysym);
    } else {
        IDEBUG ("key: %d is not modifier.", keysym);


        KeySym xlower = 0;
        KeySym xupper = 0;
        gboolean is_upper = FALSE;

        if (keysym) {
            XConvertCase (keysym, &xlower, &xupper);
            is_upper = ((guint) xupper == keysym);
        }

        gboolean is_shift_set = _is_shift_set (client);

        if (is_upper && !is_shift_set) {
            _store_modifier_state (client, IBUS_KEY_Shift_L);
        }
        keycode = _get_keysym_to_keycode (keysym);
        state = _get_modifiers_to_mask (client);
        ibus_input_context_process_key_event (client->ibuscontext,
                                              keysym,
                                              keycode,
                                              state);
        state |= IBUS_RELEASE_MASK;
        ibus_input_context_process_key_event (client->ibuscontext,
                                              keysym,
                                              keycode,
                                              state);
        if (is_upper && !is_shift_set) {
            _store_modifier_state (client, IBUS_KEY_Shift_L);
        }
    }
    return TRUE;
}
