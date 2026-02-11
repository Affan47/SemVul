editor_activate_spellchecking (GuEditor* ec, gboolean status) {
    const gchar* lang = config_get_value ("spell_language");
    GError* err = NULL;
    GError* err2 = NULL;
    GtkSpell* spell = 0;
    if (status) {
        if (! (spell = gtkspell_new_attach (ec_view, "en", &err))) {
            slog (L_ERROR, "gtkspell_new_attach (): %s\n", err->message);
            g_error_free (err);
        }
        if (!gtkspell_set_language (spell, lang, &err2)) {
            slog (L_ERROR, "gtkspell_set_language (): %s\n", err2->message);
            g_error_free (err2);
        }
    } else {
        GtkSpell* spell = gtkspell_get_from_text_view (ec_view);
        if (spell)
            gtkspell_detach (spell);
    }
}
