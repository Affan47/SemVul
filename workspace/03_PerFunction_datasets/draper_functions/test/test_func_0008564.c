translatorchooser_ok_clicked (GtkWidget *widget,
    TTRANSLATORCHOOSER *choose_t)
{
  char *szTranslator;

  if (choose_t)
    {
      if (GTK_CLIST (choose_t->translatorlist)->selection != NULL)
	{
	  gtk_clist_get_text (GTK_CLIST (choose_t->translatorlist),
	      GPOINTER_TO_INT (GTK_CLIST (choose_t->translatorlist)->
		  selection->data), 0, &szTranslator);
	  choose_t->translator = dm_SQL_A2W (szTranslator, SQL_NTS);
	}
      else
	choose_t->translator = NULL;

      choose_t->translatorlist = NULL;

      gtk_signal_disconnect_by_func (GTK_OBJECT (choose_t->mainwnd),
	  GTK_SIGNAL_FUNC (gtk_main_quit), NULL);
      gtk_main_quit ();
      gtk_widget_destroy (choose_t->mainwnd);
    }
}
