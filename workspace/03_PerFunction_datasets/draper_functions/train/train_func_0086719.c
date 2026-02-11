ibus_observed_path_new_from_xml_node (XMLNode *node,
                                     gboolean fill_stat)
{
    g_assert (node);

    IBusObservedPath *path;

    path = (IBusObservedPath *) g_object_new (IBUS_TYPE_OBSERVED_PATH, NULL);

    if (!ibus_observed_path_parse_xml_node (path, node)) {
        g_object_unref (path);
        path = NULL;
    }
    else if (fill_stat) {
        ibus_observed_path_fill_stat (path);
    }

    return path;
}
