eel_editable_label_accessible_remove_selection (AtkText *text,
						gint    selection_num)
{
  GtkWidget *widget;
  EelEditableLabel *label;
  gint select_start, select_end, caret_pos;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)

    return FALSE;

  if (selection_num != 0)
     return FALSE;

  label = EEL_EDITABLE_LABEL (widget);
  gtk_editable_get_selection_bounds (GTK_EDITABLE (label), &select_start,
                                     &select_end);

  if (select_start != select_end)
    {


      caret_pos = gtk_editable_get_position (GTK_EDITABLE (label));
      gtk_editable_select_region (GTK_EDITABLE (label), caret_pos, caret_pos);
      return TRUE;
    }
  else
    return FALSE;
}
