gst_buffer_pool_class_init (GstBufferPoolClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;

  g_type_class_add_private (klass, sizeof (GstBufferPoolPrivate));

  gobject_class->finalize = gst_buffer_pool_finalize;

  klass->start = default_start;
  klass->stop = default_stop;
  klass->set_config = default_set_config;
  klass->acquire_buffer = default_acquire_buffer;
  klass->reset_buffer = default_reset_buffer;
  klass->alloc_buffer = default_alloc_buffer;
  klass->release_buffer = default_release_buffer;
  klass->free_buffer = default_free_buffer;

  GST_DEBUG_CATEGORY_INIT (gst_buffer_pool_debug, "bufferpool", 0,
      "bufferpool debug");
}
