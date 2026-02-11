parse_printf (const struct parser_table* entry, char **argv, int *arg_ptr)
{
  const char *format;
  if (collect_arg(argv, arg_ptr, &format))
    {
      struct format_val fmt;
      open_stdout(&fmt);
      return insert_fprintf (&fmt, entry, pred_fprintf, format);
    }
  return false;
}
