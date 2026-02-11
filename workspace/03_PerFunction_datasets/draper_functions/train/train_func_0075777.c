gst_videomixer_getcaps (GstPad * pad)
{
  GstVideoMixer *mix = GST_VIDEO_MIXER (gst_pad_get_parent (pad));
  GstCaps *caps;
  GstStructure *structure;
  int numCaps;

  if (mix->master) {
    caps =
        gst_caps_copy (gst_pad_get_pad_template_caps (GST_PAD (mix->master)));
  } else {
    caps = gst_caps_copy (gst_pad_get_pad_template_caps (mix->srcpad));
  }

  numCaps = gst_caps_get_size (caps) - 1;
  for (; numCaps >= 0; numCaps--) {
    structure = gst_caps_get_structure (caps, numCaps);
    if (mix->out_width != 0) {
      gst_structure_set (structure, "width", G_TYPE_INT, mix->out_width, NULL);
    }
    if (mix->out_height != 0) {
      gst_structure_set (structure, "height", G_TYPE_INT, mix->out_height,
          NULL);
    }
    if (mix->fps_d != 0) {
      gst_structure_set (structure,
          "framerate", GST_TYPE_FRACTION, mix->fps_n, mix->fps_d, NULL);
    }
  }

  gst_object_unref (mix);

  return caps;
}
