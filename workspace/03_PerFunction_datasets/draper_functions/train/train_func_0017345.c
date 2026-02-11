channel_request_new (DBusGMethodInvocation *context,
                     ChannelRequestMethod method,
                     const char *channel_type,
                     guint handle_type,
                     guint handle,
                     gboolean suppress_handler)
{
  ChannelRequest *ret;

  g_assert (NULL != context);
  g_assert (NULL != channel_type);
  g_assert (method < NUM_METHODS);

  ret = g_slice_new0 (ChannelRequest);
  ret->context = context;
  ret->method = method;
  ret->channel_type = g_strdup (channel_type);
  ret->handle_type = handle_type;
  ret->handle = handle;
  ret->suppress_handler = suppress_handler;
  ret->yours = FALSE;

  DEBUG("New channel request at %p: ctype=%s htype=%d handle=%d suppress=%d",
        ret, channel_type, handle_type, handle, suppress_handler);

  return ret;
}
