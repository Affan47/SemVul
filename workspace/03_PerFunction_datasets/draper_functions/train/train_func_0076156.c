fm_terminal_dup_default(GError **error)
{
    FmTerminal *term = NULL;
    G_LOCK(terminal);
    if(default_terminal)
        term = g_object_ref(default_terminal);
    G_UNLOCK(terminal);
    if(!term)
        g_set_error_literal(error, G_SHELL_ERROR, G_SHELL_ERROR_EMPTY_STRING,
                            _("No terminal emulator is set in libfm config"));
    return term;
}
