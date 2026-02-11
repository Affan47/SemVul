cbf_require_value (cbf_handle handle, const char **value,
                                          const char *defaultvalue)
{
  if (cbf_get_value (handle, value) || !*value)
  {
  	 cbf_failnez (cbf_set_value(handle, defaultvalue))

  	 return (cbf_get_value(handle, value));
  }

  return 0;
}
