parameter_description(int param, struct PARAM_DESCRIPTION *pd) const
{
  switch (param) {
  case 1:
    pd->default_value = 20.0f;
    pd->description = get_parameter_name(param);
    pd->bounded_above = false;
    pd->bounded_below = true;
    pd->lower_bound = 0.0f;
    pd->toggled = false;
    pd->integer = false;
    pd->logarithmic = false;
    pd->output = false;
    break;
  default: {}
  }
}
