main (gint argc, gchar **argv)
{
    GError *error = NULL;
    GOptionContext *context;

    setlocale (LC_ALL, "");

    bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);

    context = g_option_context_new ("- ibus hangul engine component");

    g_option_context_add_main_entries (context, entries, "ibus-hangul");

    if (!g_option_context_parse (context, &argc, &argv, &error)) {
        g_print ("Option parsing failed: %s\n", error->message);
        exit (-1);
    }

    start_component ();
    return 0;
}
