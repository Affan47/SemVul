add_certificate_to_mock (Test *test,
        const gchar *certificate,
        const gchar *peer)
{
  GError *error = NULL;
  GcrCertificate *cert;
  gchar *contents;
  gsize length;
  gchar *path;

  path = g_build_filename (g_getenv ("EMPATHY_SRCDIR"),
                           "tests", "certificates", certificate, NULL);

  g_file_get_contents (path, &contents, &length, &error);
  g_assert_no_error (error);

  cert = gcr_simple_certificate_new ((const guchar *)contents, length);
  mock_module_add_certificate (cert);
  mock_module_add_assertion (cert,
          peer ? CKT_X_PINNED_CERTIFICATE : CKT_X_ANCHORED_CERTIFICATE,
          GCR_PURPOSE_SERVER_AUTH, peer);
  g_object_unref (cert);

  g_free (contents);
  g_free (path);
}
