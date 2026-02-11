config_setting_set_int64(config_setting_t *setting, long long value)
{
  switch(setting->type)
  {
    case CONFIG_TYPE_NONE:
      setting->type = CONFIG_TYPE_INT64;


    case CONFIG_TYPE_INT64:
      setting->value.llval = value;
      return(CONFIG_TRUE);

    case CONFIG_TYPE_INT:
      if((value > INT32_MAX) || (value < INT32_MIN))
        setting->value.ival = 0;
      else
        setting->value.ival = (int)value;
      return(CONFIG_TRUE);

    case CONFIG_TYPE_FLOAT:
      if(config_get_auto_convert(setting->config))
      {
        setting->value.fval = (float)value;
        return(CONFIG_TRUE);
      }
      else
        return(CONFIG_FALSE);

    default:
      return(CONFIG_FALSE);
  }
}
