_fv_text_handle_get_mode (FvTextHandle *handle)
{
  g_return_val_if_fail (FV_IS_TEXT_HANDLE (handle), FV_TEXT_HANDLE_MODE_NONE);

  return (FvTextHandleMode)handle->priv->mode;
}
