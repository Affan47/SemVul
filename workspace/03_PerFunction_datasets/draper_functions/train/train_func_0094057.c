grl_magnatune_source_new(void)
{
  GObject *object;
  GrlMagnatuneSource *source;

  GRL_DEBUG("magnatune_source_new");

  object = g_object_new(GRL_MAGNATUNE_SOURCE_TYPE,
                        "source-id", SOURCE_ID,
                        "source-name", SOURCE_NAME,
                        "source-desc", SOURCE_DESC,
                        "supported-media", GRL_MEDIA_TYPE_AUDIO,
                        NULL);

  source = GRL_MAGNATUNE_SOURCE(object);

  return source;
}
