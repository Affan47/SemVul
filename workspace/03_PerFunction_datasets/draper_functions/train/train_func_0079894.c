editable_get_chars (GtkEditable   *editable,
		    gint           start_pos,
		    gint           end_pos)
{
  EelEditableLabel *label = EEL_EDITABLE_LABEL (editable);
  int text_length;
  gint start_index, end_index;

  text_length = g_utf8_strlen (label->text, -1);

  if (end_pos < 0 || end_pos > text_length)
    end_pos = text_length;
  if (start_pos < 0)
    start_pos = 0;
  if (start_pos > end_pos)
    start_pos = end_pos;

  start_index = g_utf8_offset_to_pointer (label->text, start_pos) - label->text;
  end_index = g_utf8_offset_to_pointer (label->text, end_pos) - label->text;

  return g_strndup (label->text + start_index, end_index - start_index);
}
