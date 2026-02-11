symbolizable_get_calltip (Symbolizable *self, const gchar *symbol_name)
{
  if (!self) return NULL;
  return SYMBOLIZABLE_GET_IFACE (self)->get_calltip (self, symbol_name);
}
