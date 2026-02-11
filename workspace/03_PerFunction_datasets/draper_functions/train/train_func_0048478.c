on_initial_sign_in_done (GoaKerberosProvider *self,
                         GAsyncResult        *result,
                         GSimpleAsyncResult  *operation_result)
{
  GError    *error;
  gboolean   remember_password;
  GoaObject *object;

  object = g_simple_async_result_get_source_tag (operation_result);

  remember_password = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (operation_result),
                                                          "remember-password"));

  error = NULL;
  if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (result), &error))
    {
      g_simple_async_result_take_error (operation_result, error);
    }
  else if (remember_password)
    {
      GVariantBuilder  builder;
      const char      *object_path;

      object_path = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (result));

      if (object_path != NULL && object != NULL)
        {
          GcrSecretExchange *secret_exchange;
          const char        *password;

          secret_exchange = g_object_get_data (G_OBJECT (operation_result), "secret-exchange");
          password = gcr_secret_exchange_get_secret (secret_exchange, NULL);


          g_variant_builder_init (&builder, G_VARIANT_TYPE_VARDICT);
          g_variant_builder_add (&builder,
                                 "{sv}",
                                 "password",
                                 g_variant_new_string (password));

          error = NULL;
          goa_utils_store_credentials_for_object_sync (GOA_PROVIDER (self),
                                                       object,
                                                       g_variant_builder_end (&builder),
                                                       NULL,
                                                       NULL);
        }
    }

  g_simple_async_result_complete_in_idle (operation_result);
  g_object_unref (operation_result);
}
