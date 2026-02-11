ibus_engine_destroy (IBusEngine *engine)
{
    g_free (engine->priv->engine_name);
    engine->priv->engine_name = NULL;

    if (engine->priv->surrounding_text) {
        g_object_unref (engine->priv->surrounding_text);
        engine->priv->surrounding_text = NULL;
    }

    IBUS_OBJECT_CLASS(ibus_engine_parent_class)->destroy (IBUS_OBJECT (engine));
}
