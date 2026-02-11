_config_file_behavior_flags (conffile_t cf,
                           struct conffile_data *data,
                           char *optionname,
                           int option_type,
                           void *option_ptr,
                           int option_data,
                           void *app_ptr,
                           int app_data)
{
  unsigned int behavior_flags = 0;
  unsigned int i;

  assert (data);

  for (i = 0; i < data->stringlist_len; i++)
    {
      if (!strcasecmp (data->stringlist[i], IPMICONSOLE_BEHAVIOR_ERROR_ON_SOL_INUSE_STR))
        behavior_flags |= IPMICONSOLE_BEHAVIOR_ERROR_ON_SOL_INUSE;
      else if (!strcasecmp (data->stringlist[i], IPMICONSOLE_BEHAVIOR_DEACTIVATE_ONLY_STR))
        behavior_flags |= IPMICONSOLE_BEHAVIOR_DEACTIVATE_ONLY;
      else
        IPMICONSOLE_DEBUG (("libipmiconsole config file behavior flag invalid"));
    }

  default_config.behavior_flags = behavior_flags;

  IPMICONSOLE_DEBUG (("libipmiconsole loaded alternate default behavior flag"));
  return (0);
}
