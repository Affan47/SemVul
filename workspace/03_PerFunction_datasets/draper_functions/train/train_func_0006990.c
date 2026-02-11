skip_whitespace (cpp_reader *pfile, cppchar_t c)
{
  cpp_buffer *buffer = pfile->buffer;
  bool saw_NUL = false;

  do
    {

      if (c == ' ' || c == '\t')
	;

      else if (c == '\0')
	saw_NUL = true;
      else if (pfile->state.in_directive && CPP_PEDANTIC (pfile))
	cpp_error_with_line (pfile, CPP_DL_PEDWARN, pfile->line,
			     CPP_BUF_COL (buffer),
			     "%s in preprocessing directive",
			     c == '\f' ? "form feed" : "vertical tab");

      c = *buffer->cur++;
    }

  while (is_nvspace (c));

  if (saw_NUL)
    cpp_error (pfile, CPP_DL_WARNING, "null character(s) ignored");

  buffer->cur--;
}
