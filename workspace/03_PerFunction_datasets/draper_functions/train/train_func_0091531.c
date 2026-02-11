g_vfs_backend_http_init (GVfsBackendHttp *backend)
{
  const char         *debug;
  SoupSessionFeature *proxy_resolver;
  SoupSessionFeature *cookie_jar;
  SoupSessionFeature *content_decoder;

  g_vfs_backend_set_user_visible (G_VFS_BACKEND (backend), FALSE);

  backend->session = soup_session_sync_new_with_options ("user-agent",
                                                         "gvfs/" VERSION,
                                                         NULL);

  backend->session_async = soup_session_async_new_with_options ("user-agent",
                                                                "gvfs/" VERSION,
                                                                NULL);

  g_object_set (G_OBJECT (backend->session_async), "use-thread-context", TRUE, NULL);


  proxy_resolver = g_object_new (SOUP_TYPE_PROXY_RESOLVER_DEFAULT, NULL);
  soup_session_add_feature (backend->session, proxy_resolver);
  soup_session_add_feature (backend->session_async, proxy_resolver);
  g_object_unref (proxy_resolver);


  cookie_jar = g_object_new (SOUP_TYPE_COOKIE_JAR, NULL);
  soup_session_add_feature (backend->session, cookie_jar);
  soup_session_add_feature (backend->session_async, cookie_jar);
  g_object_unref (cookie_jar);


  g_object_set (backend->session, "accept-language-auto", TRUE, NULL);
  g_object_set (backend->session_async, "accept-language-auto", TRUE, NULL);


  content_decoder = g_object_new (SOUP_TYPE_CONTENT_DECODER, NULL);
  soup_session_add_feature (backend->session, content_decoder);
  soup_session_add_feature (backend->session_async, content_decoder);
  g_object_unref (content_decoder);


  debug = g_getenv ("GVFS_HTTP_DEBUG");
  if (debug)
    {
      SoupLogger         *logger;
      SoupLoggerLogLevel  level;

      if (g_ascii_strcasecmp (debug, "all") ||
          g_ascii_strcasecmp (debug, "body"))
        level = SOUP_LOGGER_LOG_BODY;
      else if (g_ascii_strcasecmp (debug, "header"))
        level = SOUP_LOGGER_LOG_HEADERS;
      else
        level = SOUP_LOGGER_LOG_MINIMAL;

      logger = soup_logger_new (level, DEBUG_MAX_BODY_SIZE);
      soup_session_add_feature (backend->session, SOUP_SESSION_FEATURE (logger));
      soup_session_add_feature (backend->session_async, SOUP_SESSION_FEATURE (logger));
      g_object_unref (logger);
    }

}
