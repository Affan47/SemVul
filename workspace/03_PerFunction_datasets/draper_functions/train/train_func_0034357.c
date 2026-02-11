skip_line_comment (cpp_reader *pfile)
{
  cpp_buffer *buffer = pfile->buffer;
  unsigned int orig_line = pfile->line;

  while (*buffer->cur != '\n')
    buffer->cur++;

  _cpp_process_line_notes (pfile, true);
  return orig_line != pfile->line;
}
