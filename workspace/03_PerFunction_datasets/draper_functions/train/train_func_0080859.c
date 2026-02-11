fsp_session_upload_finish               (FspSession    *self,
                                         GAsyncResult  *res,
                                         GError       **error)
{
  g_return_val_if_fail (FSP_IS_SESSION (self), NULL);
  g_return_val_if_fail (G_IS_ASYNC_RESULT (res), NULL);

  return (gchar*) _finish_async_request (G_OBJECT (self), res,
                                         fsp_session_upload,
                                         error);
}
