gst_camera_bin_stop_capture (GstCameraBin2 * camerabin)
{
  GST_DEBUG_OBJECT (camerabin, "Received stop-capture");
  if (camerabin->mode == MODE_VIDEO) {
    g_mutex_lock (&camerabin->video_capture_mutex);
    if (camerabin->video_state == GST_CAMERA_BIN_VIDEO_RECORDING) {
      if (camerabin->src)
        g_signal_emit_by_name (camerabin->src, "stop-capture", NULL);

      camerabin->video_state = GST_CAMERA_BIN_VIDEO_FINISHING;
      if (camerabin->audio_src) {
        camerabin->audio_drop_eos = FALSE;
        gst_element_send_event (camerabin->audio_src, gst_event_new_eos ());
      }
    }
    g_mutex_unlock (&camerabin->video_capture_mutex);
  }
}
