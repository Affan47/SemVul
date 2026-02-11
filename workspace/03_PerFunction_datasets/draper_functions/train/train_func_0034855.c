gst_goom_src_setcaps (GstPad * pad, GstCaps * caps)
{
  GstGoom *goom;
  GstStructure *structure;

  goom = GST_GOOM (GST_PAD_PARENT (pad));

  structure = gst_caps_get_structure (caps, 0);

  if (!gst_structure_get_int (structure, "width", &goom->width) ||
      !gst_structure_get_int (structure, "height", &goom->height) ||
      !gst_structure_get_fraction (structure, "framerate", &goom->fps_n,
          &goom->fps_d))
    return FALSE;

  goom_set_resolution (goom->plugin, goom->width, goom->height);


  goom->outsize = goom->width * goom->height * 4;
  goom->duration =
      gst_util_uint64_scale_int (GST_SECOND, goom->fps_d, goom->fps_n);
  goom->spf = gst_util_uint64_scale_int (goom->rate, goom->fps_d, goom->fps_n);
  goom->bpf = goom->spf * goom->bps;

  GST_DEBUG_OBJECT (goom, "dimension %dx%d, framerate %d/%d, spf %d",
      goom->width, goom->height, goom->fps_n, goom->fps_d, goom->spf);

  return TRUE;
}
