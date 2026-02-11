add_input_library (const char *pathname)
{
  ASSERT (called_plugin);
  if (!lang_add_input_file (xstrdup (pathname), lang_input_file_is_l_enum,
			    NULL))
    return LDPS_ERR;
  return LDPS_OK;
}
