__config_setting_get_int64(const config_setting_t *setting,
                                      long long *value)
{
  switch(setting->type)
  {
    case CONFIG_TYPE_INT64:
      *value = setting->value.llval;
      return(CONFIG_TRUE);

    case CONFIG_TYPE_INT:
      *value = (long long)(setting->value.ival);
      return(CONFIG_TRUE);

    case CONFIG_TYPE_FLOAT:
      if((setting->config->flags & CONFIG_OPTION_AUTOCONVERT) != 0)
      {
        *value = (long long)(setting->value.fval);
        return(CONFIG_TRUE);
      }
      else
      {  }

    default:
      return(CONFIG_FALSE);
  }
}
