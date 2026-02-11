_get_sub_caps (GstElementFactory * factory)
{
  const GList *templates;
  GList *walk;
  gboolean is_parser = _is_parser (factory);

  templates = gst_element_factory_get_static_pad_templates (factory);
  for (walk = (GList *) templates; walk; walk = g_list_next (walk)) {
    GstStaticPadTemplate *templ = walk->data;

    if (templ->direction == GST_PAD_SINK && templ->presence == GST_PAD_ALWAYS) {
      gboolean found = FALSE;

      if (is_parser) {
        found = TRUE;
      } else {
        guint i;

        for (i = 0; i < G_N_ELEMENTS (_sub_pad_names); i++) {
          if (strcmp (templ->name_template, _sub_pad_names[i]) == 0) {
            found = TRUE;
            break;
          }
        }
      }
      if (found)
        return gst_static_caps_get (&templ->static_caps);
    }
  }
  return NULL;
}
