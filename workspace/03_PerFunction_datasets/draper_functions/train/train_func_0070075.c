set_ibus_xkb_engine (GsdKeyboardManager *manager)
{
        IBusEngineDesc *engine;
        GsdKeyboardManagerPrivate *priv = manager->priv;

        if (!priv->ibus_engines)
                return;


        engine = g_hash_table_lookup (priv->ibus_engines, "xkb:us::eng");
        if (!engine)
                return;

        set_ibus_engine (manager, ibus_engine_desc_get_name (engine));
}
