dispose (GObject *object)
{
    CutReportFactoryBuilderPrivate *priv;

    priv = CUT_REPORT_FACTORY_BUILDER_GET_PRIVATE(object);

    if (priv->option_entries) {
        free_option_entries(priv, priv->option_entries);
        priv->option_entries = NULL;
    }

    if (priv->names) {
        g_list_foreach(priv->names, (GFunc)g_free, NULL);
        g_list_free(priv->names);
        priv->names = NULL;
    }

    if (priv->filenames) {
        g_strfreev(priv->filenames);
        priv->filenames = NULL;
    }

    G_OBJECT_CLASS(cut_report_factory_builder_parent_class)->dispose(object);
}
