abiAddStockButton (GtkDialog * me, const gchar * btn_id,
			       gint response_id)
{
	UT_return_val_if_fail(me, NULL);
	UT_return_val_if_fail(btn_id, NULL);

	GtkWidget * wid = gtk_dialog_add_button(me, btn_id, response_id);
	gtk_dialog_set_response_sensitive(me, response_id, TRUE);

	return wid;
}
