se_prop_create_xine_param (se_t *se, se_o_t *o,
				const char *id, int xine_param,
				se_prop_type_t type)
{
  switch (type)
  {
  case SE_TYPE_BOOL:
  case SE_TYPE_INT:
    se_prop_create_with_reader (se, o, id, "", type, xine_param, FALSE,
				se_prop_read_xine_param);
    return;
  default:
    g_printerr (_("script_engine: can't create property for xine param non-int type\n"));
  }
}
