gst_camerabin_change_state (GstElement * element, GstStateChange transition)
{
  GstCameraBin *camera = GST_CAMERABIN (element);
  GstStateChangeReturn ret;

  GST_DEBUG_OBJECT (element, "changing state: %s -> %s",
      gst_element_state_get_name (GST_STATE_TRANSITION_CURRENT (transition)),
      gst_element_state_get_name (GST_STATE_TRANSITION_NEXT (transition)));

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      if (!camerabin_create_elements (camera)) {
        ret = GST_STATE_CHANGE_FAILURE;
        goto done;
      }


      gst_element_set_locked_state (camera->imgbin, TRUE);
      gst_element_set_locked_state (camera->vidbin, TRUE);
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      camerabin_setup_src_elements (camera);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_PLAYING:


      camerabin_setup_view_elements (camera);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:


      if (GST_STATE (camera->imgbin) != GST_STATE_NULL) {
        gst_element_set_state (camera->imgbin, GST_STATE_READY);
      }
      if (GST_STATE (camera->vidbin) != GST_STATE_NULL) {
        gst_element_set_state (camera->vidbin, GST_STATE_READY);
      }
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      gst_element_set_locked_state (camera->imgbin, FALSE);
      gst_element_set_locked_state (camera->vidbin, FALSE);
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  GST_DEBUG_OBJECT (element, "after chaining up: %s -> %s = %s",
      gst_element_state_get_name (GST_STATE_TRANSITION_CURRENT (transition)),
      gst_element_state_get_name (GST_STATE_TRANSITION_NEXT (transition)),
      gst_element_state_change_return_get_name (ret));

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      g_mutex_lock (camera->capture_mutex);
      if (camera->capturing) {
        GST_WARNING_OBJECT (camera, "was capturing when changing to READY");
        camera->capturing = FALSE;


        gst_camerabin_reset_to_view_finder (camera);
        g_cond_signal (camera->cond);
      }


      GST_DEBUG_OBJECT (camera, "Reset processing counter to 0");
      camera->processing_counter = 0;
      g_object_notify (G_OBJECT (camera), "idle");
      g_mutex_unlock (camera->capture_mutex);


      gst_pad_set_blocked_async (camera->pad_src_view, FALSE,
          (GstPadBlockCallback) camerabin_pad_blocked, camera);

      g_signal_handlers_disconnect_by_func (camera->src_vid_src,
          gst_camerabin_scene_mode_notify_cb, camera);
      g_signal_handlers_disconnect_by_func (camera->src_vid_src,
          gst_camerabin_zoom_notify_cb, camera);
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      camerabin_destroy_elements (camera);
      break;


    case GST_STATE_CHANGE_NULL_TO_READY:
      if (ret == GST_STATE_CHANGE_FAILURE)
        camerabin_destroy_elements (camera);
      break;
    default:
      break;
  }

done:
  GST_DEBUG_OBJECT (element, "changed state: %s -> %s = %s",
      gst_element_state_get_name (GST_STATE_TRANSITION_CURRENT (transition)),
      gst_element_state_get_name (GST_STATE_TRANSITION_NEXT (transition)),
      gst_element_state_change_return_get_name (ret));

  return ret;
}
