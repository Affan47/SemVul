reader_can_handle (const char *uri) {
    int i = plugin_count;
    reader_plugin *plugin = plugins;

    if (!uri) {
	    return 0;
    }

    for (;i--;plugin++) {
	if (plugin->can_handle (uri) > 0)
	    return 1;
    }

    return 0;
}
