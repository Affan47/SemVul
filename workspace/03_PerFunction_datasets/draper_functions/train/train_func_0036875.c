ibus_key_event_from_string (const gchar *string,
                            guint       *keyval,
                            guint       *modifiers)
{
    g_return_val_if_fail (string != NULL, FALSE);
    g_return_val_if_fail (keyval != NULL, FALSE);
    g_return_val_if_fail (modifiers != NULL, FALSE);

    gchar **tokens = NULL;
    gchar **p;
    gboolean retval = FALSE;

    tokens = g_strsplit (string, "+", 0);
    g_return_val_if_fail (tokens != NULL, FALSE);

    *keyval = 0;
    *modifiers = 0;

    for (p = tokens; *(p + 1) != NULL; p++) {
        gint i;
        for (i = 0; i < 32; i++) {
            if (g_strcmp0 (modifier_name[i], *p) != 0)
                continue;
            *modifiers |= (1 << i);
            break;
        }
        if (i == 32) {
            goto _out;
        }
    }

    *keyval = ibus_keyval_from_name (*p);
    if (*keyval != IBUS_KEY_VoidSymbol)
        retval = TRUE;
_out:
    if (tokens)
        g_strfreev (tokens);
    return retval;
}
