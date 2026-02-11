xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (sizeof *result);
  if (!result)
    return NULL;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  if (!result->name)
    goto err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  switch (setting->type)
    {
    case XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      break;
    case XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      break;
    case XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      if (!result->data.v_string)
	goto err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      break;
    }

  result->last_change_serial = setting->last_change_serial;

  return result;

 err:
  if (result->name)
    free (result->name);
  free (result);

  return NULL;
}
