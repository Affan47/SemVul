bisho_utils_encode_tokens (const char *token, const char *secret)
{
  char *encoded_token, *encoded_secret;
  char *string;

  g_assert (token);
  g_assert (secret);

  encoded_token = g_base64_encode ((guchar*)token, strlen (token));
  encoded_secret = g_base64_encode ((guchar*)secret, strlen (secret));

  string = g_strconcat (encoded_token, " ", encoded_secret, NULL);

  g_free (encoded_token);
  g_free (encoded_secret);

  return string;
}
