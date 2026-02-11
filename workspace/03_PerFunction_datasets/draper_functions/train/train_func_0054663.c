process_all_startpoints(int argc, char *argv[])
{
  int i;


  for (i = 0; i < argc && !looks_like_expression(argv[i], true); i++)
    {
      state.starting_path_length = strlen(argv[i]);
      find(argv[i]);
    }

  if (i == 0)
    {


      char defaultpath[2] = ".";
      find(defaultpath);
    }
}
