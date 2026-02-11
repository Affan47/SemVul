ekiga_main_window_init_history (EkigaMainWindow *mw)
{
  GtkWidget *label = NULL;

  boost::shared_ptr<History::Source> history_source = mw->priv->core->get<History::Source> ("call-history-store");
  boost::shared_ptr<History::Book> history_book = history_source->get_book ();

  mw->priv->call_history_view = call_history_view_gtk_new (history_book);

  label = gtk_label_new (_("Call history"));
  mw->priv->call_history_page_number =
    gtk_notebook_append_page (GTK_NOTEBOOK (mw->priv->main_notebook), mw->priv->call_history_view, label);
  g_signal_connect (mw->priv->call_history_view, "selection-changed",
		    G_CALLBACK (on_history_selection_changed), mw);
}
