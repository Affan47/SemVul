handle_gio_error(const char *msg,
			     GError **err,
			     bool show_dialog=true)
{
  if((*err)!=NULL && (*err)->code==G_IO_CHANNEL_ERROR_PIPE)
    {
      g_error_free(*err);
      *err=NULL;
      return false;
    }
  else
    return handle_gerror(msg, err, show_dialog);
}
