eel_editable_label_accessible_get_default_attributes (AtkText *text)
{
  GtkWidget *widget;
  EelEditableLabel *label;
  AtkAttributeSet *at_set = NULL;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)

    return NULL;

  label = EEL_EDITABLE_LABEL (widget);

  at_set = gail_misc_get_default_attributes (at_set,
                                             eel_editable_label_get_layout (label),
                                             widget);
  return at_set;
}
