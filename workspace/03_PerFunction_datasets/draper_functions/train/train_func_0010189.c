osc_coerce_arguments(const char *u_dsc, const char *p_dsc, osc_data_t *data)
{
  u_dsc++;
  p_dsc++;
  while(*u_dsc != '\0') {
    osc_coerce(*u_dsc++, *p_dsc++, data++);
  }
}
