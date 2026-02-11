get_link_name_at (const char *name, int dir_fd, char *relname)
{
  struct link_name_args args;
  args.result = NULL;
  args.name = name;
  args.relname = relname;
  if (0 == run_in_dir(dir_fd, get_link_name_cb, &args))
    return args.result;
  else
    return NULL;
}
