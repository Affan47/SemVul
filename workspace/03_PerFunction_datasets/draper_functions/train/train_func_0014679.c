polkit_backend_authority_check_authorization_finish (PolkitBackendAuthority  *authority,
                                                     GAsyncResult            *res,
                                                     GError                 **error)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  if (klass->check_authorization_finish == NULL)
    {
      g_warning ("check_authorization_finish is not implemented (it is not optional)");
      g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (res), error);
      return NULL;
    }
  else
    {
      return klass->check_authorization_finish (authority, res, error);
    }
}
