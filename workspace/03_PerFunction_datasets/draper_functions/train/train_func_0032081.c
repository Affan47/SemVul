_factory_can_handle_caps (GstElementFactory * factory, const GstCaps * caps,
    GstPadDirection dir, gboolean exact)
{
  const GList *templates;

  templates = gst_element_factory_get_static_pad_templates (factory);
  while (templates) {
    GstStaticPadTemplate *template = (GstStaticPadTemplate *) templates->data;

    if (template->direction == dir) {
      GstCaps *tmp = gst_static_caps_get (&template->static_caps);

      if ((exact && _gst_caps_match (caps, tmp)) ||
          (!exact && gst_caps_can_intersect (tmp, caps))) {
        gst_caps_unref (tmp);
        return TRUE;
      }
      gst_caps_unref (tmp);
    }
    templates = g_list_next (templates);
  }

  return FALSE;
}
