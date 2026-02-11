ibus_hotkey_profile_remove_hotkey (IBusHotkeyProfile *profile,
                                   guint              keyval,
                                   guint              modifiers)
{
    IBusHotkeyProfilePrivate *priv;
    priv = IBUS_HOTKEY_PROFILE_GET_PRIVATE (profile);

    modifiers = normalize_modifiers (keyval, modifiers & priv->mask);

    IBusHotkey hotkey = {
        .keyval = keyval,
        .modifiers = modifiers
    };

    IBusHotkey *p1;
    GQuark event;
    gboolean retval;

    retval = g_tree_lookup_extended (priv->hotkeys,
                                     &hotkey,
                                     (gpointer)&p1,
                                     (gpointer)&event);

    if (!retval)
        return FALSE;

    gint i;
    IBusHotkeyEvent *p2 = NULL;
    for ( i = 0; i < priv->events->len; i++) {
        p2 = &g_array_index (priv->events, IBusHotkeyEvent, i);
        if (p2->event == event)
            break;
    }

    g_assert (p2->event == event);

    p2->hotkeys = g_list_remove (p2->hotkeys, p1);
    if (p2->hotkeys == NULL) {
        g_array_remove_index_fast (priv->events, i);
    }

    g_tree_remove (priv->hotkeys, p1);

    return TRUE;
}
