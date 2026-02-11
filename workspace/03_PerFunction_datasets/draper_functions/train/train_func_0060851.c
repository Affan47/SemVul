gst_camerabin_image_create_elements (GstCameraBinImage * img)
{
  gboolean ret = FALSE;
  g_return_val_if_fail (img != NULL, FALSE);

  if (gst_camerabin_image_prepare_elements (img)) {
    ret = gst_camerabin_image_link_elements (img);
  }

  return ret;
}
