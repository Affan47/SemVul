gst_video_buffer_pool_new ()
{
  GstVideoBufferPool *pool;

  pool = g_object_new (GST_TYPE_VIDEO_BUFFER_POOL, NULL);

  GST_LOG_OBJECT (pool, "new video buffer pool %p", pool);

  return GST_BUFFER_POOL_CAST (pool);
}
