string_prop (const char *name, const char *value)
{
  SmProp *prop;

  prop = g_new (SmProp, 1);
  prop->name = (char *)name;
  prop->type = SmARRAY8;

  prop->num_vals = 1;
  prop->vals = g_new (SmPropValue, 1);

  prop->vals[0].length = strlen (value);
  prop->vals[0].value = (char *)value;

  return prop;
}
