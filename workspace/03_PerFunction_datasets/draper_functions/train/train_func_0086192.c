polkit_authority_enumerate_temporary_authorizations_finish (PolkitAuthority *authority,
                                                            GAsyncResult    *res,
                                                            GError         **error)
{
  GList *ret;
  GVariant *value;
  GVariantIter iter;
  GVariant *child;
  GVariant *array;
  GAsyncResult *_res;

  g_return_val_if_fail (POLKIT_IS_AUTHORITY (authority), NULL);
  g_return_val_if_fail (G_IS_SIMPLE_ASYNC_RESULT (res), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  ret = NULL;

  g_warn_if_fail (g_simple_async_result_get_source_tag (G_SIMPLE_ASYNC_RESULT (res)) == polkit_authority_enumerate_temporary_authorizations);
  _res = G_ASYNC_RESULT (g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (res)));

  value = g_dbus_proxy_call_finish (authority->proxy, _res, error);
  if (value == NULL)
    goto out;

  array = g_variant_get_child_value (value, 0);
  g_variant_iter_init (&iter, array);
  while ((child = g_variant_iter_next_value (&iter)) != NULL)
    {
      PolkitTemporaryAuthorization *auth;
      auth = polkit_temporary_authorization_new_for_gvariant (child, error);
      g_variant_unref (child);
      if (auth == NULL)
        {
          g_prefix_error (error, "Error serializing return value of EnumerateTemporaryAuthorizations: ");
          g_list_foreach (ret, (GFunc) g_object_unref, NULL);
          g_list_free (ret);
          goto out;
        }
      ret = g_list_prepend (ret, auth);
    }
  ret = g_list_reverse (ret);
  g_variant_unref (array);
  g_variant_unref (value);

 out:
  return ret;
}
