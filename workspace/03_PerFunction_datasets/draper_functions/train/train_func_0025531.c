on_handle_questions (Ekiga::FormRequestPtr request,
                     gpointer data)
{
  FormDialog dialog (request, GTK_WIDGET (data));

  dialog.run ();

  return true;
}
