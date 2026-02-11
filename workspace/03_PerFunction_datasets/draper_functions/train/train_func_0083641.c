lam_ssi_base_module_register(char *type, lt_dlhandle module_handle,
                             lam_ssi_t *module_struct)
{
  int size, i;
  module_registry_item_t *new_item, **m = lam_arr_get(modules);

  new_item = malloc(sizeof(module_registry_item_t));
  if (new_item == NULL)
    return LAMERROR;

  new_item->mri_type = strdup(type);
  new_item->mri_dlhandle = module_handle;
  new_item->mri_module_struct = module_struct;
  new_item->mri_refcount = 1;
  new_item->mri_dependencies = lam_arr_init(sizeof(int), NULL);


  size = lam_arr_size(modules);
  for (i = 0; i < size; ++i) {
    if (m[i] == NULL) {
      m[i] = new_item;
      new_item = NULL;
    }
  }


  if (new_item != NULL) {
    lam_arr_append(modules, &new_item);
  }

  return 0;
}
