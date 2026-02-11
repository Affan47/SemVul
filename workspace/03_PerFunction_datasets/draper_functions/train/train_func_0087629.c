gst_selector_pad_finalize (GObject * object)
{
  RsnSelectorPad *pad;

  pad = GST_SELECTOR_PAD_CAST (object);

  if (pad->tags)
    gst_tag_list_unref (pad->tags);
  gst_selector_pad_free_cached_buffers (pad);

  G_OBJECT_CLASS (gst_selector_pad_parent_class)->finalize (object);
}
