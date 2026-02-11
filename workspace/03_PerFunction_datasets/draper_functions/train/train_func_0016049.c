IIS_ProcessCmdlList(const char* param_filename, int (*pFunction)(int, TEXTCHAR**))
{


  FDKFILE *config_fp;
  int argc;
  char *line_ptr;

#ifdef CMDFILE_PREFIX
  FDKstrcpy(tmp, CMDFILE_PREFIX);
  FDKstrcpy(tmp+FDKstrlen(CMDFILE_PREFIX), param_filename);

  config_fp = FDKfopen(tmp, "r");
#else

  config_fp = FDKfopen(param_filename, "r");
#endif

  if(config_fp == NULL)
  {
#ifdef CMDFILE_PREFIX
    FDKprintf("\ncould not open config file %s", tmp);
#else
    FDKprintf("\ncould not open config file %s", param_filename);
#endif
    return 1;
  }


  while (FDKfgets(line, CMDL_MAX_STRLEN*CMDL_MAX_ARGC, config_fp) != NULL)
  {
    argc = 1;


    line_ptr =  (char*)FDKstrchr(line, '\n');
    if (line_ptr != NULL)
      *line_ptr = ' ';

    line_ptr = line;


    do {

      while (*line_ptr == ' ' && line_ptr < line+CMDL_MAX_STRLEN)
        line_ptr++;

      argv_ptr[argc] = line_ptr;

      line_ptr = (char*)FDKstrchr(line_ptr, ' ');

      if (line_ptr != NULL) {

        *line_ptr = 0;

        line_ptr++;

      }
      argc++;
    } while ( line_ptr != NULL && argc < CMDL_MAX_ARGC);


    if (argc > 2 && *argv_ptr[1] != '#' && FDKstrlen(argv_ptr[1])>1)
    {
      int retval;

      retval = (*pFunction)(argc, argv_ptr);

      FDKprintf("main returned %d\n", retval);
    }
  }

  FDKfclose(config_fp);
  return 0;
}
