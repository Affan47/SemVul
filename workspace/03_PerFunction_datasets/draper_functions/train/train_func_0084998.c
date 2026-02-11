gail_canvas_text_get_run_attributes (AtkText *text,
                                     gint offset,
                                     gint *start_offset,
                                     gint *end_offset)
{
  GailCanvasText *gail_text;

  g_return_val_if_fail (GAIL_IS_CANVAS_TEXT (text), NULL);
  gail_text = GAIL_CANVAS_TEXT (text);
  g_return_val_if_fail (gail_text->textutil, NULL);

  return gail_misc_buffer_get_run_attributes (gail_text->textutil->buffer,
					      offset, start_offset, end_offset);
}
