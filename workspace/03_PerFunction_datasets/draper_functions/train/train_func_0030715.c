save_filename(const char *filename, lt_ptr data)
{
  int len, prefix_len, total_len;
  char *prefix;
  const char *basename;
  module_file_t module_file;
  ltfn_data_holder_t *params = (ltfn_data_holder_t *) data;


  len = sizeof(module_template) + strlen(params->type) + 32;
  if (params->name != NULL)
    len += strlen(params->name);
  prefix = malloc(len);
  snprintf(prefix, len, module_template, params->type);
  prefix_len = strlen(prefix);
  if (params->name != NULL)
    strcat(prefix, params->name);
  total_len = strlen(prefix);

  basename = strrchr(filename, '/');
  if (basename == NULL)
    basename = filename;
  else
    basename += 1;

  if (strncmp(basename, prefix, total_len) != 0) {
    free(prefix);
    return 0;
  }


  module_file.type = strdup(params->type);
  module_file.name = strdup(basename + prefix_len);
  module_file.basename = strdup(basename);
  module_file.filename = strdup(filename);
  module_file.status = UNVISITED;
  lam_arr_append(found_files, &module_file);


  free(prefix);
  return 0;
}
