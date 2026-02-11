ibus_hotkey_profile_filter_key_event (IBusHotkeyProfile *profile,
                                      guint              keyval,
                                      guint              modifiers,
                                      guint              prev_keyval,
                                      guint              prev_modifiers,
                                      gpointer           user_data)
{
    IBusHotkeyProfilePrivate *priv;
    priv = IBUS_HOTKEY_PROFILE_GET_PRIVATE (profile);

    modifiers = normalize_modifiers (keyval, modifiers & priv->mask);
    prev_modifiers = normalize_modifiers (prev_keyval, prev_modifiers & priv->mask);

    IBusHotkey hotkey = {
        .keyval = keyval,
        .modifiers = modifiers,
    };

    if (modifiers & IBUS_RELEASE_MASK) {

        if (prev_modifiers & IBUS_RELEASE_MASK)
            return 0;


        if (modifiers != (prev_modifiers | IBUS_RELEASE_MASK))
            return 0;


        if ((keyval != prev_keyval) &&
            (is_modifier (keyval) == FALSE ||
             is_modifier (prev_keyval) == FALSE))
            return 0;
    }

    GQuark event = (GQuark) GPOINTER_TO_UINT (g_tree_lookup (priv->hotkeys, &hotkey));

    if (event != 0) {
        g_signal_emit (profile, profile_signals[TRIGGER], event, user_data);
    }

    return event;
}
