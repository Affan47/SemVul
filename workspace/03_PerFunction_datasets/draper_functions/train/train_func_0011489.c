find_param(const char *full_pname, const char *rest_of_pname, bx_param_c *base)
{
  const char *from = rest_of_pname;
  char component[BX_PATHNAME_LEN];
  char *to = component;


  while (*from != 0 && *from != '.') {
    *to = *from;
    to++;
    from++;
  }
  *to = 0;
  if (!component[0]) {
    BX_PANIC(("find_param: found empty component in parameter name '%s'", full_pname));

  }
  if (base->get_type() != BXT_LIST) {
    BX_PANIC(("find_param: base was not a list!"));
  }
  BX_DEBUG(("searching for component '%s' in list '%s'", component, base->get_name()));


  bx_list_c *list = (bx_list_c *)base;
  bx_param_c *child = list->get_by_name(component);

  if (child == NULL) return NULL;
  if (from[0] == 0) {

    return child;
  }

  BX_ASSERT(from[0] == '.');
  from++;
  return find_param(full_pname, from, child);
}
