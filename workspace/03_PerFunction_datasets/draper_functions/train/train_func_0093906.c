url_changed_cb (GtkEditable *e,
		gpointer data)
{
  EkigaMainWindow *mw = EKIGA_MAIN_WINDOW (data);
  const char *tip_text = NULL;

  tip_text = gtk_entry_get_text (GTK_ENTRY (e));

  if (g_strrstr (tip_text, "@") == NULL) {
    boost::shared_ptr<Opal::Bank> bank = mw->priv->core->get<Opal::Bank> ("opal-account-store");
    if (bank) {
      gtk_list_store_clear (mw->priv->completion);
      bank->visit_accounts (boost::bind (&account_completion_helper_cb, _1, tip_text, mw));
    }
  }

  gtk_widget_set_tooltip_text (GTK_WIDGET (e), tip_text);
}
