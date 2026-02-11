cmafec_preset_get_parameter(int index)
{
  struct cma_preset *ppreset;

  fc_assert_ret_val(index >= 0 && index < cmafec_preset_num(), NULL);

  ppreset = preset_list_get(preset_list, index);
  return &ppreset->parameter;
}
