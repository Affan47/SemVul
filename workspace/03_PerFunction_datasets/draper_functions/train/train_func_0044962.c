evd_pki_pubkey_encrypt_finish (EvdPkiPubkey  *self,
                               GAsyncResult  *result,
                               gsize         *size,
                               GError       **error)
{
  GSimpleAsyncResult *res = G_SIMPLE_ASYNC_RESULT (result);

  g_return_val_if_fail (EVD_IS_PKI_PUBKEY (self), NULL);
  g_return_val_if_fail (g_simple_async_result_is_valid (result,
                                                        G_OBJECT (self),
                                                        evd_pki_pubkey_decrypt),
                        NULL);

  if (! g_simple_async_result_propagate_error (res, error))
    {
      GString *data;
      gchar *ret;

      data = g_simple_async_result_get_op_res_gpointer (res);
      ret = data->str;
      data->str = NULL;

      if (size != NULL)
        *size = data->len;

      return ret;
    }
  else
    return NULL;
}
