dispose_directories() {
    if (datadir)
        g_free(datadir);
    if (docdir)
        g_free(docdir);
    if (icondir)
        g_free(icondir);
    if (uidir)
        g_free(uidir);
    if (gladedir)
        g_free(gladedir);
    if (plugindir)
        g_free(plugindir);
    if (scriptdir)
        g_free(scriptdir);
}
