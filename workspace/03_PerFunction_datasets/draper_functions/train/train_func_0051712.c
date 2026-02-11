elem_is_dynamic (GstElement * element, GstDecodeBin * decode_bin)
{
  GList *pads;


  for (pads = GST_ELEMENT_GET_CLASS (element)->padtemplates; pads;
      pads = g_list_next (pads)) {
    GstPadTemplate *templ = GST_PAD_TEMPLATE (pads->data);
    const gchar *templ_name;


    if (GST_PAD_TEMPLATE_DIRECTION (templ) != GST_PAD_SRC)
      continue;

    templ_name = GST_PAD_TEMPLATE_NAME_TEMPLATE (templ);
    GST_DEBUG_OBJECT (decode_bin, "got a source pad template %s", templ_name);


    switch (GST_PAD_TEMPLATE_PRESENCE (templ)) {
      case GST_PAD_SOMETIMES:
      {


        GstPad *pad = gst_element_get_static_pad (element, templ_name);

        if (pad) {
          GST_DEBUG_OBJECT (decode_bin, "got the pad for sometimes template %s",
              templ_name);
          gst_object_unref (pad);
        } else {
          GST_DEBUG_OBJECT (decode_bin,
              "did not get the sometimes pad of template %s", templ_name);

          return TRUE;
        }
        break;
      }
      default:

        break;
    }
  }
  return FALSE;
}
