peas_engine_init (PeasEngine *engine)
{


  if (default_engine == NULL)
    {
      default_engine = engine;
      g_object_add_weak_pointer (G_OBJECT (engine),
                                 (gpointer *) &default_engine);
    }

  engine->priv = G_TYPE_INSTANCE_GET_PRIVATE (engine,
                                              PEAS_TYPE_ENGINE,
                                              PeasEnginePrivate);

  engine->priv->in_dispose = FALSE;
}
