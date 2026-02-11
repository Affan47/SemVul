webx_dialog_response (GtkWidget *widget,
                      gint       response_id,
                      gpointer   data)
{
  switch (response_id)
    {
    case GTK_RESPONSE_OK:
      if (webx_dialog_save_dialog (WEBX_DIALOG (widget)))
        {
          webx_dialog_close (WEBX_DIALOG (widget));
        }
      break;

    default:
      webx_dialog_close (WEBX_DIALOG (widget));
      break;
    }
}
