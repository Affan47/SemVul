editable_set_selection_bounds (GtkEditable *editable,
			       gint         start,
			       gint         end)
{
  EelEditableLabel *label = EEL_EDITABLE_LABEL (editable);
  int text_length;
  gint start_index, end_index;

  text_length = g_utf8_strlen (label->text, -1);

  if (end < 0 || end > text_length)
    end = text_length;
  if (start < 0)
    start = text_length;
  if (start > text_length)
    start = text_length;

  eel_editable_label_reset_im_context (label);

  start_index = g_utf8_offset_to_pointer (label->text, start) - label->text;
  end_index = g_utf8_offset_to_pointer (label->text, end) - label->text;

  eel_editable_label_select_region_index (label, start_index, end_index);
}
