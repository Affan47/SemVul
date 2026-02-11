menu_activate (GtkWidget        *item,
               ExoHelperChooser *chooser)
{
  static const gchar *CATEGORY_ERRORS[] =
  {
    N_("Failed to set default Web Browser"),
    N_("Failed to set default Mail Reader"),
    N_("Failed to set default File Manager"),
    N_("Failed to set default Terminal Emulator"),
  };

  ExoHelper *helper;
  GtkWidget *message;
  GError    *error = NULL;


  g_assert (EXO_HELPER_N_CATEGORIES == G_N_ELEMENTS (CATEGORY_ERRORS));

  g_return_if_fail (GTK_IS_WIDGET (item));
  g_return_if_fail (EXO_IS_HELPER_CHOOSER (chooser));


  helper = g_object_get_data (G_OBJECT (item), I_("exo-helper"));
  if (G_LIKELY (helper != NULL))
    {
      if (!exo_helper_database_set_default (chooser->database, chooser->category, helper, &error))
        {
          message = gtk_message_dialog_new (GTK_WINDOW (chooser),
                                            GTK_DIALOG_DESTROY_WITH_PARENT
                                            | GTK_DIALOG_MODAL,
                                            GTK_MESSAGE_ERROR,
                                            GTK_BUTTONS_CLOSE,
                                            "%s.", _(CATEGORY_ERRORS[chooser->category]));
          gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (message), "%s.", error->message);
          gtk_dialog_run (GTK_DIALOG (message));
          gtk_widget_destroy (message);
          g_error_free (error);
        }
      else
        {

          exo_helper_chooser_update (chooser);
        }
    }
}
