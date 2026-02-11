tpaw_account_settings_parameter_is_valid (
    TpawAccountSettings *settings,
    const gchar *param)
{
  const GRegex *regex;

  g_return_val_if_fail (TPAW_IS_ACCOUNT_SETTINGS (settings), FALSE);

  if (g_list_find_custom (settings->priv->required_params, param,
        (GCompareFunc) g_strcmp0))
    {

      if (g_hash_table_lookup (settings->priv->parameters, param) != NULL)
        goto test_regex;


      if (settings->priv->account != NULL &&
          !tpaw_account_settings_is_unset (settings, param))
        {
          const GHashTable *account_params;

          account_params = tp_account_get_parameters (
              settings->priv->account);
          if (tp_asv_lookup (account_params, param))
            goto test_regex;
        }

      return FALSE;
    }

test_regex:

  regex = g_hash_table_lookup (settings->priv->param_regexps, param);
  if (regex)
    {
      gchar *value;
      gboolean match;

      value = tpaw_account_settings_dup_string (settings, param);
      if (value == NULL)
        return FALSE;

      match = g_regex_match (regex, value, 0, NULL);

      g_free (value);
      return match;
    }

  return TRUE;
}
