gst_element_class_add_pad_template (GstElementClass * klass,
    GstPadTemplate * templ)
{
  GList *template_list = klass->padtemplates;

  g_return_if_fail (GST_IS_ELEMENT_CLASS (klass));
  g_return_if_fail (GST_IS_PAD_TEMPLATE (templ));


  while (template_list) {
    GstPadTemplate *padtempl = (GstPadTemplate *) template_list->data;


    if (strcmp (templ->name_template, padtempl->name_template) == 0) {
      gst_object_unref (padtempl);
      template_list->data = templ;
      return;
    }
    template_list = g_list_next (template_list);
  }


  gst_object_ref_sink (templ);

  klass->padtemplates = g_list_append (klass->padtemplates, templ);
  klass->numpadtemplates++;
}
