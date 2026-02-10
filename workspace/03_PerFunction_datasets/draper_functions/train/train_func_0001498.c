cancel(GtkWidget *, gpointer data)
{
  DialogWindow *self = (DialogWindow *)data;

  self->_dialog_result = GTK_RESPONSE_CANCEL;

  if (self->_args != NULL)
    self->_args->call_callbacks("ui-dialog-cancel-CB");

  self->hide();
}
