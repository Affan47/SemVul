img_capture_prepared (gpointer data, GstCaps * caps)
{
  GstCameraBin *camera = GST_CAMERABIN (data);

  GST_INFO_OBJECT (camera, "image capture prepared");


  if (!gst_caps_is_equal (camera->image_capture_caps, caps)) {
    gst_camerabin_adapt_image_capture (camera, caps);
  } else {
    gst_camerabin_set_capsfilter_caps (camera, camera->image_capture_caps);
  }

  g_object_set (G_OBJECT (camera->src_out_sel), "resend-latest", FALSE,
      "active-pad", camera->pad_src_img, NULL);
}
