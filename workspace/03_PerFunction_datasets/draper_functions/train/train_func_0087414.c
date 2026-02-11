gst_element_class_get_pad_template (GstElementClass *
    element_class, const gchar * name)
{
  GList *padlist;

  g_return_val_if_fail (GST_IS_ELEMENT_CLASS (element_class), NULL);
  g_return_val_if_fail (name != NULL, NULL);

  padlist = element_class->padtemplates;

  while (padlist) {
    GstPadTemplate *padtempl = (GstPadTemplate *) padlist->data;

    if (strcmp (padtempl->name_template, name) == 0)
      return padtempl;

    padlist = g_list_next (padlist);
  }

  return NULL;
}
