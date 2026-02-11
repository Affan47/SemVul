retrieve_pin_for_pinfile (const char *pinfile, struct ck_token_info *token_info,
                          int attempts, ck_user_type_t user_type, struct p11_kit_pin **pin)
{
  unsigned int flags = 0;
  struct p11_kit_uri *token_uri;
  struct p11_kit_pin *result;
  char *label;

  label = p11_kit_space_strdup (token_info->label, sizeof (token_info->label));
  if (label == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_MEMORY_ERROR;
    }

  token_uri = p11_kit_uri_new ();
  if (token_uri == NULL)
    {
      free (label);
      gnutls_assert ();
      return GNUTLS_E_MEMORY_ERROR;
    }

  memcpy (p11_kit_uri_get_token_info (token_uri), token_info,
          sizeof (struct ck_token_info));

  if (attempts)
    flags |= P11_KIT_PIN_FLAGS_RETRY;
  if (user_type == CKU_USER)
    {
      flags |= P11_KIT_PIN_FLAGS_USER_LOGIN;
      if (token_info->flags & CKF_USER_PIN_COUNT_LOW)
        flags |= P11_KIT_PIN_FLAGS_MANY_TRIES;
      if (token_info->flags & CKF_USER_PIN_FINAL_TRY)
        flags |= P11_KIT_PIN_FLAGS_FINAL_TRY;
    }
  else if (user_type == CKU_SO)
    {
      flags |= P11_KIT_PIN_FLAGS_SO_LOGIN;
      if (token_info->flags & CKF_SO_PIN_COUNT_LOW)
        flags |= P11_KIT_PIN_FLAGS_MANY_TRIES;
      if (token_info->flags & CKF_SO_PIN_FINAL_TRY)
        flags |= P11_KIT_PIN_FLAGS_FINAL_TRY;
    }
  else if (user_type == CKU_CONTEXT_SPECIFIC)
    {
      flags |= P11_KIT_PIN_FLAGS_CONTEXT_LOGIN;
    }

  result = p11_kit_pin_request (pinfile, token_uri, label, flags);
  p11_kit_uri_free (token_uri);
  free (label);

  if (result == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_PKCS11_PIN_ERROR;
    }

  *pin = result;
  return 0;
}
