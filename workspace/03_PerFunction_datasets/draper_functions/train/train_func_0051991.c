my_print_default_files(const char *conf_file)
{
  const char *empty_list[]= { "", 0 };
  my_bool have_ext= fn_ext(conf_file)[0] != 0;
  const char **exts_to_use= have_ext ? empty_list : f_extensions;
  char name[FN_REFLEN], **ext;

  puts("\nDefault options are read from the following files in the given order:");

  if (dirname_length(conf_file))
    fputs(conf_file,stdout);
  else
  {
    const char **dirs;
    MEM_ROOT alloc;
    init_alloc_root(&alloc,512,0);

    if ((dirs= init_default_directories(&alloc)) == NULL)
    {
      fputs("Internal error initializing default directories list", stdout);
    }
    else
    {
      for ( ; *dirs; dirs++)
      {
        for (ext= (char**) exts_to_use; *ext; ext++)
        {
          const char *pos;
          char *end;
          if (**dirs)
            pos= *dirs;
          else if (my_defaults_extra_file)
            pos= my_defaults_extra_file;
          else
            continue;
          end= convert_dirname(name, pos, NullS);
          if (name[0] == FN_HOMELIB)
            *end++= '.';
          strxmov(end, conf_file, *ext, " ", NullS);
          fputs(name, stdout);
        }
      }
    }

    free_root(&alloc, MYF(0));
  }
  puts("");
}
