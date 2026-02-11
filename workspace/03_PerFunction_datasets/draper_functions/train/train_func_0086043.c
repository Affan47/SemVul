metadata_write_probe (GstPad * pad, GstBuffer * buffer, gpointer u_data)
{

  GstCameraBinImage *img = NULL;
  GstTagSetter *setter = NULL;
  GstPad *srcpad = NULL;
  GstCaps *caps = NULL;
  GstStructure *st = NULL;

  img = GST_CAMERABIN_IMAGE (u_data);

  g_return_val_if_fail (img != NULL, TRUE);

  if (GST_IS_TAG_SETTER (img->formatter)) {
    setter = GST_TAG_SETTER (img->formatter);
  }

  if (!setter) {
    GST_WARNING_OBJECT (img, "setting tags failed");
    goto done;
  }


  gst_tag_setter_add_tags (setter, GST_TAG_MERGE_REPLACE,
      GST_TAG_CODEC, "Image", NULL);

  if (img->enc) {
    srcpad = gst_element_get_static_pad (img->enc, "src");
  }
  GST_LOG_OBJECT (img, "srcpad:%" GST_PTR_FORMAT, srcpad);
  if (srcpad) {
    caps = gst_pad_get_negotiated_caps (srcpad);
    GST_LOG_OBJECT (img, "caps:%" GST_PTR_FORMAT, caps);
    if (caps) {

      if (gst_caps_get_size (caps) != 1) {
        GST_WARNING_OBJECT (img, "can't decide structure for format tag");
        goto done;
      }
      st = gst_caps_get_structure (caps, 0);
      if (st) {
        GST_DEBUG_OBJECT (img, "Xmp.dc.format:%s", gst_structure_get_name (st));
        gst_tag_setter_add_tags (setter, GST_TAG_MERGE_REPLACE,
            GST_TAG_VIDEO_CODEC, gst_structure_get_name (st), NULL);
      }
    }
  }
done:
  if (caps)
    gst_caps_unref (caps);
  if (srcpad)
    gst_object_unref (srcpad);

  return TRUE;
}
