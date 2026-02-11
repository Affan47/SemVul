add_import_paths (bool stdinc)
{

  if (stdinc)
    {
      char *phobos_dir = prefixed_path (D_PHOBOS_DIR);
      char *target_dir = prefixed_path (D_PHOBOS_TARGET_DIR);

      if (multilib_dir)
	target_dir = concat (target_dir, "/", multilib_dir, NULL);

      global.params.imppath->shift (phobos_dir);
      global.params.imppath->shift (target_dir);
    }


  add_env_var_paths ("D_IMPORT_PATH");


  if (global.params.imppath)
    {
      for (size_t i = 0; i < global.params.imppath->dim; i++)
	{
	  char *path = (*global.params.imppath)[i];
	  if (path)
	    add_import_path (FileName::splitPath (path));
	}
    }


  if (global.params.fileImppath)
    {
      for (size_t i = 0; i < global.params.fileImppath->dim; i++)
	{
	  char *path = (*global.params.fileImppath)[i];
	  if (path)
	    add_fileimp_path (FileName::splitPath (path));
	}
    }
}
