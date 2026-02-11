lam_ssi_base_param_find(char *type, char *module, char *param)
{
  int i, size;
  lam_ssi_base_param_t *array;


  if (PUB(params) == NULL)
    return LAMERROR;
  if (type == NULL || param == NULL)
    return LAMERROR;


  array = lam_arr_get(PUB(params));
  size = lam_arr_size(PUB(params));
  for (i = 0; i < size; ++i) {
    if (strcmp(type, array[i].lsbp_type_name) == 0 &&
        ((module == NULL && array[i].lsbp_module_name == NULL) ||
         (module != NULL && array[i].lsbp_module_name != NULL &&
          strcmp(module, array[i].lsbp_module_name) == 0)) &&
        strcmp(param, array[i].lsbp_param_name) == 0)
      return i;
  }


  return LAMERROR;
}
