set_atk_name_description (GtkWidget *widget, const gchar *name,
                          const gchar *description)
{
  AtkObject *aobj;
  aobj = gtk_widget_get_accessible (widget);

  if (GTK_IS_ACCESSIBLE (aobj) == FALSE)
     return;
  if (name)
     atk_object_set_name (aobj, name);
  if (description)
     atk_object_set_description (aobj, description);
}
