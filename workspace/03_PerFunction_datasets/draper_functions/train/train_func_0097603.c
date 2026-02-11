check_after_analyze()
{
  if (!PROJECT_name || PROJECT_name[0] == 0)
    raise_error("No project name");

  if (!PROJECT_startup || PROJECT_startup[0] == 0)
    raise_error("No startup class");

  if (!PROJECT_title || PROJECT_title[0] == 0)
    PROJECT_title = PROJECT_name;
}
