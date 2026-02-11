glkunix_startup_code(glkunix_startup_t *data)
{
  if(!process_arguments(data->argc, data->argv)) return 0;

#ifdef GARGLK
  garglk_set_program_name("Bocfel");
  if(game_file != NULL)
  {
    char *p = strrchr(game_file, '/');
    garglk_set_story_name(p == NULL ? game_file : p + 1);
  }
#endif

  return 1;
}
