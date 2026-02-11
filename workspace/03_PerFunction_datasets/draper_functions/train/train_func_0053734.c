cheese_camera_setup (CheeseCamera *camera, const gchar *uuid, GError **error)
{
  CheeseCameraPrivate *priv;
  GError  *tmp_error = NULL;
  GstElement *video_sink;

  g_return_if_fail (error == NULL || *error == NULL);
  g_return_if_fail (CHEESE_IS_CAMERA (camera));

  priv = camera->priv;

  cheese_camera_detect_camera_devices (camera);

  if (priv->num_camera_devices < 1)
  {
    g_set_error (error, CHEESE_CAMERA_ERROR, CHEESE_CAMERA_ERROR_NO_DEVICE, _("No device found"));
    return;
  }

  if (uuid != NULL)
  {
    cheese_camera_set_device_by_dev_uuid (camera, uuid);
  }


  if ((priv->camerabin = gst_element_factory_make ("camerabin", "camerabin")) == NULL)
  {
    cheese_camera_set_error_element_not_found (error, "camerabin");
  }
  if ((priv->camera_source = gst_element_factory_make ("wrappercamerabinsrc", "camera_source")) == NULL)
  {
    cheese_camera_set_error_element_not_found (error, "wrappercamerabinsrc");
  }
  g_object_set (priv->camerabin, "camera-source", priv->camera_source, NULL);


  if ((video_sink = gst_element_factory_make ("autocluttersink",
                                              "cluttersink")) == NULL)
  {
    cheese_camera_set_error_element_not_found (error, "cluttervideosink");
    return;
  }
  g_object_set (G_OBJECT (video_sink), "texture", priv->video_texture,
                "async-handling", FALSE, NULL);
  g_object_set (G_OBJECT (priv->camerabin), "viewfinder-sink", video_sink, NULL);


  cheese_camera_set_camera_source (camera);
  cheese_camera_set_video_recording (camera, &tmp_error);
  cheese_camera_create_video_filter_bin (camera, &tmp_error);

  if (tmp_error != NULL || (error != NULL && *error != NULL))
  {
    g_propagate_prefixed_error (error, tmp_error,
                                _("One or more needed GStreamer elements are missing: "));
    GST_WARNING ("%s", (*error)->message);
    return;
  }

  g_object_set (G_OBJECT (priv->camera_source), "video-source-filter", priv->video_filter_bin, NULL);

  priv->bus = gst_element_get_bus (priv->camerabin);
  gst_bus_add_signal_watch (priv->bus);

  g_signal_connect (G_OBJECT (priv->bus), "message",
                    G_CALLBACK (cheese_camera_bus_message_cb), camera);
}
