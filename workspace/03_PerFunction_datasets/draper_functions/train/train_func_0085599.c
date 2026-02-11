gphpedit_file_browser_dispose (GObject *object)
{
  gphpeditFileBrowserPrivate *priv;

  priv = FILEBROWSER_BACKEND_GET_PRIVATE(object);


  if (g_signal_handler_is_connected (priv->fbbackend, priv->handlerid)){
   g_signal_handler_disconnect(priv->fbbackend, priv->handlerid);
  }
  if (g_signal_handler_is_connected (priv->fbbackend, priv->handleridchange)){
   g_signal_handler_disconnect(priv->fbbackend,   priv->handleridchange);
  }
  filebrowser_backend_cancel (priv->fbbackend);


  G_OBJECT_CLASS (gphpedit_file_browser_parent_class)->dispose (object);
}
