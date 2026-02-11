gst_camerabin_set_videosrc_zoom (GstCameraBin * camera, gfloat zoom)
{
  gboolean ret = FALSE;


  if (GST_IS_ELEMENT (camera->src_vid_src) &&
      gst_element_implements_interface (camera->src_vid_src,
          GST_TYPE_PHOTOGRAPHY)) {
    gst_photography_set_zoom (GST_PHOTOGRAPHY (camera->src_vid_src), zoom);
    ret = TRUE;
  }
  return ret;
}
