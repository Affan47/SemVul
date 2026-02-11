g_pkcs11_slot_get_token_info (GPkcs11Slot       *self,
                              CK_TOKEN_INFO_PTR  token_info)
{
  CK_RV rv;

  g_return_val_if_fail (G_IS_PKCS11_SLOT (self), FALSE);
  g_return_val_if_fail (token_info, FALSE);

  memset (token_info, 0, sizeof (CK_TOKEN_INFO));
  rv = (self->priv->module->C_GetTokenInfo) (self->priv->slot_id, token_info);
  if (rv == CKR_TOKEN_NOT_PRESENT)
    return FALSE;

  if (rv != CKR_OK)
    {
      g_warning ("call to C_GetTokenInfo on PKCS#11 module failed: %s",
                 p11_kit_strerror (rv));
      return FALSE;
    }

  return TRUE;
}
