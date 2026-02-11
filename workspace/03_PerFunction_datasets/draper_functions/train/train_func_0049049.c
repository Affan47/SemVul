set_password_prompt_if_needed (TpawAccountSettings *ac_settings,
    const gchar *password)
{
  gboolean prompt;

  prompt = !tp_str_empty (password);

  if (prompt == tpaw_account_settings_get_boolean (ac_settings,
        "password-prompt"))
    return FALSE;

  tpaw_account_settings_set (ac_settings, "password-prompt",
      g_variant_new_boolean (prompt));

  return TRUE;
}
