lan_session_limit_commit (const char *section_name,
                          const struct config_keyvalue *kv,
                          void *arg)
{
  bmc_config_state_data_t *state_data;
  struct user_access ua;
  unsigned int username_not_set_yet = 0;
  config_err_t ret;

  assert (section_name);
  assert (kv);
  assert (arg);

  state_data = (bmc_config_state_data_t *)arg;


  if ((ret = _get_user_access (state_data,
                               section_name,
                               kv->key->key_name,
                               &ua,
                               &username_not_set_yet)) != CONFIG_ERR_SUCCESS)
    return (ret);


  return (_set_user_access (state_data,
                            section_name,
                            kv->key->key_name,
                            &ua,
                            NULL));
}
