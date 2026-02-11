polkit_authorization_result_get_dismissed (PolkitAuthorizationResult *result)
{
  gboolean ret;
  PolkitDetails *details;

  g_return_val_if_fail (POLKIT_IS_AUTHORIZATION_RESULT (result), FALSE);

  ret = FALSE;
  details = polkit_authorization_result_get_details (result);
  if (details != NULL && polkit_details_lookup (details, "polkit.dismissed") != NULL)
    ret = TRUE;

  return ret;
}
