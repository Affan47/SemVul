gftp_disconnect (gftp_request * request)
{
  g_return_if_fail (request != NULL);

#ifdef USE_SSL
  if (request->ssl != NULL)
    {
      SSL_free (request->ssl);
      request->ssl = NULL;
    }
#endif

#if GLIB_MAJOR_VERSION > 1
  if (request->iconv_from_initialized)
    {
      g_iconv_close (request->iconv_from);
      request->iconv_from_initialized = 0;
    }

  if (request->iconv_to_initialized)
    {
      g_iconv_close (request->iconv_to);
      request->iconv_to_initialized = 0;
    }

  if (request->iconv_charset)
  {
    g_free (request->iconv_charset);
    request->iconv_charset = NULL;
  }
#endif

  request->cached = 0;
  if (request->disconnect == NULL)
    return;
  request->disconnect (request);
}
