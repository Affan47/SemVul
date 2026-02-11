gst_text_render_fixate_caps (GstTextRender * render, GstCaps * caps)
{
  GstStructure *s;

  caps = gst_caps_truncate (caps);

  caps = gst_caps_make_writable (caps);
  s = gst_caps_get_structure (caps, 0);

  GST_DEBUG ("Fixating caps %" GST_PTR_FORMAT, caps);
  gst_structure_fixate_field_nearest_int (s, "width", MAX (render->image_width,
          DEFAULT_RENDER_WIDTH));
  gst_structure_fixate_field_nearest_int (s, "height",
      MAX (render->image_height + render->ypad, DEFAULT_RENDER_HEIGHT));
  caps = gst_caps_fixate (caps);
  GST_DEBUG ("Fixated to    %" GST_PTR_FORMAT, caps);

  return caps;
}
