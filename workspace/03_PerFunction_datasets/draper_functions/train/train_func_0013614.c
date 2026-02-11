gst_camerabin_monitor_video_source_properties (GstCameraBin * camera)
{
  GST_DEBUG_OBJECT (camera, "checking for photography interface support");
  if (GST_IS_ELEMENT (camera->src_vid_src) &&
      gst_element_implements_interface (camera->src_vid_src,
          GST_TYPE_PHOTOGRAPHY)) {
    gint scene_mode;
    GST_DEBUG_OBJECT (camera,
        "connecting to %" GST_PTR_FORMAT " - notify::scene-mode",
        camera->src_vid_src);
    g_signal_connect (G_OBJECT (camera->src_vid_src), "notify::scene-mode",
        (GCallback) gst_camerabin_scene_mode_notify_cb, camera);
    g_object_get (G_OBJECT (camera->src_vid_src), "scene-mode", &scene_mode,
        NULL);
    camera->night_mode = scene_mode == GST_PHOTOGRAPHY_SCENE_MODE_NIGHT;

    GST_DEBUG_OBJECT (camera,
        "connecting to %" GST_PTR_FORMAT " - notify::zoom",
        camera->src_vid_src);
    g_signal_connect (G_OBJECT (camera->src_vid_src), "notify::zoom",
        (GCallback) gst_camerabin_zoom_notify_cb, camera);
  }
}
