gst_camera_bin_dispose (GObject * object)
{
  GstCameraBin2 *camerabin = GST_CAMERA_BIN2_CAST (object);

  g_free (camerabin->location);
  g_mutex_clear (&camerabin->preview_list_mutex);
  g_mutex_clear (&camerabin->image_capture_mutex);
  g_mutex_clear (&camerabin->video_capture_mutex);
  g_cond_clear (&camerabin->video_state_cond);

  if (camerabin->src_capture_notify_id)
    g_signal_handler_disconnect (camerabin->src,
        camerabin->src_capture_notify_id);
  if (camerabin->src)
    gst_object_unref (camerabin->src);
  if (camerabin->user_src)
    gst_object_unref (camerabin->user_src);

  if (camerabin->audio_src)
    gst_object_unref (camerabin->audio_src);
  if (camerabin->user_audio_src)
    gst_object_unref (camerabin->user_audio_src);

  if (camerabin->audio_capsfilter)
    gst_object_unref (camerabin->audio_capsfilter);
  if (camerabin->audio_volume)
    gst_object_unref (camerabin->audio_volume);

  if (camerabin->viewfinderbin)
    gst_object_unref (camerabin->viewfinderbin);
  if (camerabin->viewfinderbin_queue)
    gst_object_unref (camerabin->viewfinderbin_queue);
  if (camerabin->viewfinderbin_capsfilter)
    gst_object_unref (camerabin->viewfinderbin_capsfilter);

  if (camerabin->video_encodebin_signal_id)
    g_signal_handler_disconnect (camerabin->video_encodebin,
        camerabin->video_encodebin_signal_id);

  if (camerabin->videosink)
    gst_object_unref (camerabin->videosink);
  if (camerabin->video_encodebin)
    gst_object_unref (camerabin->video_encodebin);
  if (camerabin->videobin_capsfilter)
    gst_object_unref (camerabin->videobin_capsfilter);

  if (camerabin->image_encodebin_signal_id)
    g_signal_handler_disconnect (camerabin->image_encodebin,
        camerabin->image_encodebin_signal_id);
  if (camerabin->imagesink)
    gst_object_unref (camerabin->imagesink);
  if (camerabin->image_encodebin)
    gst_object_unref (camerabin->image_encodebin);
  if (camerabin->imagebin_capsfilter)
    gst_object_unref (camerabin->imagebin_capsfilter);

  if (camerabin->video_filter)
    gst_object_unref (camerabin->video_filter);
  if (camerabin->image_filter)
    gst_object_unref (camerabin->image_filter);
  if (camerabin->viewfinder_filter)
    gst_object_unref (camerabin->viewfinder_filter);
  if (camerabin->audio_filter)
    gst_object_unref (camerabin->audio_filter);

  if (camerabin->user_video_filter)
    gst_object_unref (camerabin->user_video_filter);
  if (camerabin->user_audio_filter)
    gst_object_unref (camerabin->user_audio_filter);
  if (camerabin->user_image_filter)
    gst_object_unref (camerabin->user_image_filter);
  if (camerabin->user_viewfinder_filter)
    gst_object_unref (camerabin->user_viewfinder_filter);

  if (camerabin->video_profile)
    gst_encoding_profile_unref (camerabin->video_profile);
  if (camerabin->image_profile)
    gst_encoding_profile_unref (camerabin->image_profile);

  if (camerabin->preview_caps)
    gst_caps_replace (&camerabin->preview_caps, NULL);
  if (camerabin->preview_filter) {
    gst_object_unref (camerabin->preview_filter);
    camerabin->preview_filter = NULL;
  }

  G_OBJECT_CLASS (parent_class)->dispose (object);
}
