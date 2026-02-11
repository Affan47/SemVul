clutter_text_buffer_normal_delete_text (ClutterTextBuffer *buffer,
                                     guint           position,
                                     guint           n_chars)
{
  ClutterTextBufferPrivate *pv = buffer->priv;
  gsize start, end;

  if (position > pv->normal_text_chars)
    position = pv->normal_text_chars;
  if (position + n_chars > pv->normal_text_chars)
    n_chars = pv->normal_text_chars - position;

  if (n_chars > 0)
    {
      start = g_utf8_offset_to_pointer (pv->normal_text, position) - pv->normal_text;
      end = g_utf8_offset_to_pointer (pv->normal_text, position + n_chars) - pv->normal_text;

      g_memmove (pv->normal_text + start, pv->normal_text + end, pv->normal_text_bytes + 1 - end);
      pv->normal_text_chars -= n_chars;
      pv->normal_text_bytes -= (end - start);


      trash_area (pv->normal_text + pv->normal_text_bytes + 1, end - start - 1);

      clutter_text_buffer_emit_deleted_text (buffer, position, n_chars);
    }

  return n_chars;
}
