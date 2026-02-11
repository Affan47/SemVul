execute(void)
  {
    if (get_vdip()->get_file() != NULL)
      add_error(ERR_FILE_OPEN);
    else if (get_arg_count() == 1)
      execute_with_name(get_arg(0));
    else if (get_arg_count() >= 2)
      execute_with_name_and_time(get_arg(0), get_dword_arg(1));
    else
      add_error(ERR_BAD_COMMAND);
  }
