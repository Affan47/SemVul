warn_format_string (enum is_format is_format[NFORMATS], const char *string,
                    lex_pos_ty *pos, const char *pretty_msgstr)
{
  if (possible_format_p (is_format[format_python])
      && get_python_format_unnamed_arg_count (string) > 1)
    {
      char buffer[21];

      error_with_progname = false;
      if (pos->line_number == (size_t)(-1))
        buffer[0] = '\0';
      else
        sprintf (buffer, ":%ld", (long) pos->line_number);
      multiline_warning (xasprintf (_("%s%s: warning: "),
                                    pos->file_name, buffer),
                         xasprintf (_("\
'%s' format string with unnamed arguments cannot be properly localized:\n\
The translator cannot reorder the arguments.\n\
Please consider using a format string with named arguments,\n\
and a mapping instead of a tuple for the arguments.\n"),
                                    pretty_msgstr));
      error_with_progname = true;
    }
}
