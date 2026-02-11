gst_pad_finalize (GObject * object)
{
  GstPad *pad = GST_PAD_CAST (object);
  GstTask *task;


  if ((task = GST_PAD_TASK (pad))) {
    gst_task_join (task);
    GST_PAD_TASK (pad) = NULL;
    gst_object_unref (task);
  }

  if (pad->stream_rec_lock) {
    g_static_rec_mutex_free (pad->stream_rec_lock);
    g_slice_free (GStaticRecMutex, pad->stream_rec_lock);
    pad->stream_rec_lock = NULL;
  }
  if (pad->preroll_lock) {
    g_mutex_free (pad->preroll_lock);
    g_cond_free (pad->preroll_cond);
    pad->preroll_lock = NULL;
    pad->preroll_cond = NULL;
  }
  if (pad->block_cond) {
    g_cond_free (pad->block_cond);
    pad->block_cond = NULL;
  }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
