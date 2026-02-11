print_1_line (line_flag, line)
     char const *line_flag;
     char const * const *line;
{
  char const *text = line[0], *limit = line[1];
  char const *flag_format = 0;


  if (line_flag && *line_flag)
    {
      flag_format = tab_align_flag ? "%s\t" : "%s ";
      printf_output (flag_format, line_flag);
    }

  output_1_line (text, limit, flag_format, line_flag);

  if ((!line_flag || line_flag[0]) && limit[-1] != '\n')
    printf_output ("\n\\ No newline at end of file\n");
}
