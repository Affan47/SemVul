on_got_identity_for_sign_out (GoaIdentityManager *manager,
                              GAsyncResult       *result,
                              GSimpleAsyncResult *operation_result)
{
  GError *error;
  GoaIdentity *identity;

  error = NULL;
  identity = goa_identity_manager_get_identity_finish (manager, result, &error);

  if (error != NULL)
    {
      goa_debug ("GoaIdentityService: Identity could not be signed out: %s",
                 error->message);
      return;
    }

  g_object_set_data_full (G_OBJECT (operation_result),
                          "identity",
                          g_object_ref (identity),
                          (GDestroyNotify)
                          g_object_unref);

  goa_identity_manager_sign_identity_out (manager,
                                          identity,
                                          NULL,
                                          (GAsyncReadyCallback)
                                          on_identity_signed_out,
                                          operation_result);
}
