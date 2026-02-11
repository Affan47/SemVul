gst_camerabin_preview_pipeline_post (GstCameraBinPreviewPipelineData * preview,
    GstSample * sample)
{
  g_return_val_if_fail (preview != NULL, FALSE);
  g_return_val_if_fail (preview->pipeline != NULL, FALSE);
  g_return_val_if_fail (sample, FALSE);

  g_mutex_lock (&preview->processing_lock);
  g_return_val_if_fail (preview->pipeline != NULL, FALSE);

  if (preview->pending_preview_caps) {
    if (preview->processing > 0) {
      g_cond_wait (&preview->processing_cond, &preview->processing_lock);
    }
    _gst_camerabin_preview_set_caps (preview, preview->pending_preview_caps);
    gst_caps_replace (&preview->pending_preview_caps, NULL);
  }

  preview->processing++;

  g_object_set (preview->appsrc, "caps", gst_sample_get_caps (sample), NULL);
  gst_app_src_push_buffer ((GstAppSrc *) preview->appsrc,
      gst_buffer_ref (gst_sample_get_buffer (sample)));

  g_mutex_unlock (&preview->processing_lock);

  return TRUE;
}
