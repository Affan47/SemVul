load_gfx_file(const char *gfx_filename)
{
  const char **gfx_fileexts = gfx_fileextensions(), *gfx_fileext;
  struct sprite *s;


  while ((gfx_fileext = *gfx_fileexts++)) {
    const char *real_full_name;
    char full_name[strlen(gfx_filename) + strlen(gfx_fileext) + 2];

    sprintf(full_name, "%s.%s", gfx_filename, gfx_fileext);
    if ((real_full_name = fileinfoname(get_data_dirs(), full_name))) {
      log_debug("trying to load gfx file \"%s\".", real_full_name);
      s = load_gfxfile(real_full_name);
      if (s) {
        return s;
      }
    }
  }

  log_error("Could not load gfx file \"%s\".", gfx_filename);
  return NULL;
}
