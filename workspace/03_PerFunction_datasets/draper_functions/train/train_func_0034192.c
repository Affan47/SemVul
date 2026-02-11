gst_dfbvideosink_finalize (GObject * object)
{
  GstDfbVideoSink *dfbvideosink;

  dfbvideosink = GST_DFBVIDEOSINK (object);

  if (dfbvideosink->par) {
    g_free (dfbvideosink->par);
    dfbvideosink->par = NULL;
  }
  if (dfbvideosink->pool_lock) {
    g_mutex_free (dfbvideosink->pool_lock);
    dfbvideosink->pool_lock = NULL;
  }
  if (dfbvideosink->setup) {
    gst_dfbvideosink_cleanup (dfbvideosink);
  }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
