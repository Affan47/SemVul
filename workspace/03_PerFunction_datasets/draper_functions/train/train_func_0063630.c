cmafec_preset_get_index_of_parameter(const struct cm_parameter
					 *const parameter)
{
  int i;

  for (i = 0; i < preset_list_size(preset_list); i++) {
    struct cma_preset *ppreset = preset_list_get(preset_list, i);
    if (cm_are_parameter_equal(&ppreset->parameter, parameter)) {
      return i;
    }
  }
  return -1;
}
