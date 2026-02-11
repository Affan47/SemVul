transfer_current_call_cb (G_GNUC_UNUSED GtkWidget *widget,
			  gpointer data)
{
  EkigaCallWindow *cw = EKIGA_CALL_WINDOW (data);

  g_return_if_fail (data != NULL);
  ekiga_call_window_transfer_dialog_run (EKIGA_CALL_WINDOW (cw), GTK_WIDGET (data), NULL);
}
