lam_ssi_base_module_find(char *directory, char *type,
                         lam_ssi_t *static_modules[],
                         lam_ssi_t ***modules_out)
{
  int i, size;
  lam_ssi_t **array;


  found_modules = lam_arr_init(sizeof(lam_ssi_t *), NULL);
  for (i = 0; static_modules[i] != NULL; ++i)
    lam_arr_append(found_modules, &static_modules[i]);


  find_modules(directory, type, NULL, static_modules);


  size = lam_arr_size(found_modules);
  array = (lam_ssi_t **) lam_arr_get(found_modules);
  *modules_out = malloc(sizeof(lam_ssi_t *) * (size + 1));
  if (*modules_out == NULL)
    return LAMERROR;
  for (i = 0; i < size; ++i)
    (*modules_out)[i] = array[i];
  (*modules_out)[i] = NULL;
  lam_arr_free(found_modules);
  found_modules = NULL;


  return 0;
}
