sign_out_identity (GoaKerberosIdentityManager *self,
                   Operation                  *operation)
{
  GError *error;
  gboolean was_signed_out;
  char *identity_name;

  identity_name =
    goa_kerberos_identity_get_principal_name (GOA_KERBEROS_IDENTITY
                                              (operation->identity));
  goa_debug ("GoaKerberosIdentityManager: signing out identity %s", identity_name);
  g_free (identity_name);

  error = NULL;
  was_signed_out =
    goa_kerberos_identity_erase (GOA_KERBEROS_IDENTITY (operation->identity),
                                 &error);

  if (!was_signed_out)
    {
      goa_debug ("GoaKerberosIdentityManager: could not sign out identity: %s",
               error->message);
      g_error_free (error);
    }
}
