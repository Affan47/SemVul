cut_stream_factory_builder_init (CutStreamFactoryBuilder *builder)
{
    CutStreamFactoryBuilderPrivate *priv;
    const gchar *dir;

    priv = CUT_STREAM_FACTORY_BUILDER_GET_PRIVATE(builder);
    priv->names = NULL;

    dir = g_getenv("CUT_STREAM_FACTORY_MODULE_DIR");
    if (!dir) {
#ifdef G_OS_WIN32
        if (!win32_stream_factory_module_dir)
            win32_stream_factory_module_dir =
                cut_win32_build_factory_module_dir_name("stream");
        dir = win32_stream_factory_module_dir;
#else
        dir = STREAM_FACTORY_MODULEDIR;
#endif
    }

    g_object_set(G_OBJECT(builder),
                 "module-dir", dir,
                 NULL);
    cut_module_factory_load(dir, "stream");
}
