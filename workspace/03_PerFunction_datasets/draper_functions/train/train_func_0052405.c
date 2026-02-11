lexmark_describe_resolution(const stp_vars_t *v, int *x, int *y)
{
  const char *resolution = stp_get_string_parameter(v, "Resolution");
  const lexmark_res_t *res =
    lexmark_get_resolution_para(stp_get_model_id(v), resolution);

  if (res)
    {
      *x = res->hres;
      *y = res->vres;
      return;
    }
  *x = -1;
  *y = -1;
}
