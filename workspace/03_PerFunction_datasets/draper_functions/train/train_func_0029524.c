d_number_component (struct d_info *di)
{
  struct demangle_component *ret = d_make_empty (di);
  if (ret)
    {
      ret->type = DEMANGLE_COMPONENT_NUMBER;
      ret->u.s_number.number = d_number (di);
    }
  return ret;
}
