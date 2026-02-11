set_label_bold (GtkLabel * label, gboolean make_bold)
{
  PangoAttrList *attrlist;
  PangoAttribute *attr;

  g_assert (label != NULL);

  attrlist = gtk_label_get_attributes (label);
  if (!attrlist)
    attrlist = pango_attr_list_new ();

  if (make_bold) {
    attr = pango_attr_weight_new (PANGO_WEIGHT_BOLD);
    attr->start_index = 0;
    attr->end_index = -1;
    pango_attr_list_change (attrlist, attr);
  } else {
    attr = pango_attr_weight_new (PANGO_WEIGHT_NORMAL);
    attr->start_index = 0;
    attr->end_index = -1;
    pango_attr_list_change (attrlist, attr);
  }
  gtk_label_set_attributes (label, attrlist);
}
