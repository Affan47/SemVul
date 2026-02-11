gst_camerabin_preview_set_caps (GstCameraBinPreviewPipelineData * preview,
    GstCaps * caps)
{
  g_return_if_fail (preview != NULL);

  g_mutex_lock (preview->processing_lock);

  if (preview->processing == 0) {
    _gst_camerabin_preview_set_caps (preview, caps);
  } else {
    GST_DEBUG ("Preview pipeline busy, storing new caps as pending");
    gst_caps_replace (&preview->pending_preview_caps, caps);
  }
  g_mutex_unlock (preview->processing_lock);
}
