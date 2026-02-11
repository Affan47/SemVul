evd_http_request_class_init (EvdHttpRequestClass *class)
{
  GObjectClass *obj_class = G_OBJECT_CLASS (class);

  obj_class->dispose = evd_http_request_dispose;
  obj_class->finalize = evd_http_request_finalize;
  obj_class->get_property = evd_http_request_get_property;
  obj_class->set_property = evd_http_request_set_property;

  g_object_class_install_property (obj_class, PROP_METHOD,
                                   g_param_spec_string ("method",
                                                        "Method",
                                                        "The HTTP method of the request (GET, POST, HEAD, etc)",
                                                        SOUP_METHOD_GET,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                                                        G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (obj_class, PROP_PATH,
                                   g_param_spec_string ("path",
                                                        "URI path",
                                                        "The full path portion of the requested URL",
                                                        "",
                                                        G_PARAM_READABLE |
                                                        G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (obj_class, PROP_URI,
                                   g_param_spec_boxed ("uri",
                                                       "Request URI",
                                                       "The URI of the requested resource",
                                                       SOUP_TYPE_URI,
                                                       G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                                                       G_PARAM_STATIC_STRINGS));

  g_type_class_add_private (obj_class, sizeof (EvdHttpRequestPrivate));
}
