e_date_edit_set_editable (EDateEdit *dedit,
                          gboolean editable)
{
	EDateEditPrivate *priv;

	g_return_if_fail (E_IS_DATE_EDIT (dedit));

	priv = dedit->priv;

	gtk_editable_set_editable (GTK_EDITABLE (priv->date_entry), editable);
	gtk_widget_set_sensitive (priv->date_button, editable);
}
