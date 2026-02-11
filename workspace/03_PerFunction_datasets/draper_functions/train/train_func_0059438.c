empathy_audio_sink_request_new_pad (GstElement *element,
  GstPadTemplate *templ,
  const gchar* name,
  const GstCaps *caps)
#else
static GstPad *
empathy_audio_sink_request_new_pad (GstElement *element,
  GstPadTemplate *templ,
  const gchar* name)
#endif
{
  EmpathyGstAudioSink *self = EMPATHY_GST_AUDIO_SINK (element);
  GstElement *bin, *resample, *audioconvert0, *audioconvert1;
  GstPad *pad = NULL;
  GstPad *subpad, *filterpad;

  bin = gst_bin_new (NULL);

  audioconvert0 = gst_element_factory_make ("audioconvert", NULL);
  if (audioconvert0 == NULL)
    goto error;

  gst_bin_add (GST_BIN (bin), audioconvert0);

  resample = gst_element_factory_make ("audioresample", NULL);
  if (resample == NULL)
    goto error;

  gst_bin_add (GST_BIN (bin), resample);

  audioconvert1 = gst_element_factory_make ("audioconvert", NULL);
  if (audioconvert1 == NULL)
    goto error;

  gst_bin_add (GST_BIN (bin), audioconvert1);

  self->priv->sink = create_sink (self);
  if (self->priv->sink == NULL)
    goto error;

  if (GST_IS_STREAM_VOLUME (self->priv->sink))
    {
      g_mutex_lock (&self->priv->volume_mutex);
      if (self->priv->volume_idle_id == 0)
        self->priv->volume_idle_id = g_idle_add (
          empathy_audio_sink_volume_idle_setup, self);
      g_mutex_unlock (&self->priv->volume_mutex);
    }
  else
    {
      gchar *n = gst_element_get_name (self->priv->sink);

      DEBUG ("Element %s doesn't support volume", n);
      g_free (n);
    }

  gst_bin_add (GST_BIN (bin), self->priv->sink);

  if (!gst_element_link_many (audioconvert0, resample, audioconvert1,
      self->priv->sink, NULL))
    goto error;

  filterpad = gst_element_get_static_pad (audioconvert0, "sink");

  if (filterpad == NULL)
    goto error;

  subpad = gst_ghost_pad_new ("sink", filterpad);
  gst_object_unref (filterpad);

  if (!gst_element_add_pad (GST_ELEMENT (bin), subpad))
    goto error;

  gst_bin_add (GST_BIN (self), bin);

  pad = gst_ghost_pad_new (name, subpad);
  g_assert (pad != NULL);

  if (!gst_element_sync_state_with_parent (bin))
    goto error;

  if (!gst_pad_set_active (pad, TRUE))
    goto error;

  if (!gst_element_add_pad (GST_ELEMENT (self), pad))
    goto error;

  return pad;

error:
  if (pad != NULL)
    {
      gst_object_unref (pad);
    }

  gst_object_unref (bin);
  g_warning ("Failed to create output subpipeline");
  return NULL;
}
