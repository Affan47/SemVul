gst_camerabin_capture_start (GstCameraBin * camera)
{

  GST_INFO_OBJECT (camera, "starting capture");
  if (camera->paused) {
    gst_camerabin_capture_pause (camera);
    return;
  }

  if (!camera->active_bin) {
    GST_INFO_OBJECT (camera, "mode not explicitly set by application");
    gst_camerabin_change_mode (camera, camera->mode);
    if (!camera->active_bin) {
      GST_ELEMENT_ERROR (camera, CORE, FAILED,
          ("starting capture failed"), (NULL));
    }
  }


  if (g_str_equal (camera->filename->str, ""))
    if (camera->active_bin == camera->vidbin || !camera->preview_caps) {
      GST_ELEMENT_ERROR (camera, CORE, FAILED,
          ("set filename before starting capture"), (NULL));
      return;
    }

  g_mutex_lock (camera->capture_mutex);
  if (camera->capturing) {
    GST_WARNING_OBJECT (camera, "capturing \"%s\" ongoing, set new filename",
        camera->filename->str);


    g_mutex_unlock (camera->capture_mutex);
    return;
  }
  CAMERABIN_PROCESSING_INC_UNLOCKED (camera);
  g_mutex_unlock (camera->capture_mutex);

  GST_OBJECT_LOCK (camera);
  camera->block_viewfinder_trigger = camera->block_viewfinder_prop;
  GST_OBJECT_UNLOCK (camera);

  if (camera->active_bin) {
    if (camera->active_bin == camera->imgbin) {
      GST_INFO_OBJECT (camera, "starting image capture");
      gst_camerabin_start_image_capture (camera);
    } else if (camera->active_bin == camera->vidbin) {
      GST_INFO_OBJECT (camera,
          "setting video filename and starting video capture");
      g_object_set (G_OBJECT (camera->active_bin), "filename",
          camera->filename->str, NULL);
      gst_camerabin_start_video_recording (camera);
    }
  }

  g_object_notify (G_OBJECT (camera), "ready-for-capture");
}
