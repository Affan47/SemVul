gamgi_gtk_dialog_global_remove (void)
{


if (gamgi->message != NULL)
  gamgi_gtk_dialog_remove (gamgi->message, &gamgi->message);
if (gamgi->question != NULL)
gamgi_gtk_dialog_remove (gamgi->question, &gamgi->question);
}
