gst_tag_inject_transform_ip (GstBaseTransform * trans, GstBuffer * buf)
{
  GstTagInject *self = GST_TAG_INJECT (trans);

  if (G_UNLIKELY (!self->tags_sent)) {
    self->tags_sent = TRUE;

    if (self->tags && !gst_tag_list_is_empty (self->tags)) {
      GST_DEBUG ("tag event :%" GST_PTR_FORMAT, self->tags);
      gst_element_found_tags (GST_ELEMENT (trans),
          gst_tag_list_copy (self->tags));
    }
  }

  return GST_FLOW_OK;
}
