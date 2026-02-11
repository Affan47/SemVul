cmdline_parser_free (struct gengetopt_args_info *args_info)
{
  cmdline_parser_release (args_info);
  if (cmd_line_list)
    {

      while (cmd_line_list) {
        cmd_line_list_tmp = cmd_line_list;
        cmd_line_list = cmd_line_list->next;
        free (cmd_line_list_tmp->string_arg);
        free (cmd_line_list_tmp);
      }
    }
}
