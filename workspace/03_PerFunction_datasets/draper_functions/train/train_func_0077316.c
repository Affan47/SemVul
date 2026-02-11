goa_identity_service_handle_sign_in (GoaIdentityServiceManager *manager,
                                     GDBusMethodInvocation     *invocation,
                                     const char                *identifier,
                                     GVariant                  *details)
{
  GoaIdentityService     *self = GOA_IDENTITY_SERVICE (manager);
  GSimpleAsyncResult     *operation_result;
  GoaIdentitySignInFlags  flags;
  char                   *secret_key;
  gconstpointer           initial_password;
  GCancellable           *cancellable;

  secret_key = NULL;
  initial_password = NULL;

  read_sign_in_details (manager, details, &flags, &secret_key);

  if (secret_key != NULL)
    {
      GcrSecretExchange *secret_exchange;

      secret_exchange = g_hash_table_lookup (self->priv->key_holders,
                                             g_dbus_method_invocation_get_sender (invocation));

      if (secret_exchange == NULL)
        {
          g_free (secret_key);
          g_dbus_method_invocation_return_error (invocation,
                                                 GOA_IDENTITY_MANAGER_ERROR,
                                                 GOA_IDENTITY_MANAGER_ERROR_ACCESSING_CREDENTIALS,
                                                 _("initial secret passed before secret key exchange"));
          return TRUE;
        }

      gcr_secret_exchange_receive (secret_exchange, secret_key);
      g_free (secret_key);

      initial_password = gcr_secret_exchange_get_secret (secret_exchange, NULL);
    }

  operation_result = g_simple_async_result_new (G_OBJECT (self),
                                                (GAsyncReadyCallback)
                                                on_sign_in_handled,
                                                g_object_ref (invocation),
                                                g_strdup (identifier));
  cancellable = g_cancellable_new ();
  g_object_set_data (G_OBJECT (operation_result),
                     "cancellable",
                     cancellable);
  g_object_set_data (G_OBJECT (operation_result),
                     "initial-password",
                     (gpointer)
                     initial_password);
  g_object_set_data (G_OBJECT (operation_result),
                     "flags",
                     GINT_TO_POINTER ((int) flags));

  sign_in (self,
           identifier,
           initial_password,
           flags,
           cancellable,
           (GAsyncReadyCallback)
           on_sign_in_done,
           operation_result);

  g_object_unref (cancellable);

  return TRUE;
}
