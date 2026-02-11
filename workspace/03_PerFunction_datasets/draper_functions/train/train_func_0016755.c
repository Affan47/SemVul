gst_dialog_require_authentication_for_widget (GstDialog *xd, GtkWidget *w)
{
	GstDialogPrivate *priv;
	GstWidgetPolicy *policy;

	g_return_if_fail (GST_IS_DIALOG (xd));
	g_return_if_fail (GTK_IS_WIDGET (w));

	priv = GST_DIALOG_GET_PRIVATE (xd);
	policy = g_new0 (GstWidgetPolicy, 1);

	policy->was_sensitive = gtk_widget_get_sensitive (w);

	g_object_set_qdata_full (G_OBJECT (w), widget_policy_quark,
				 policy, (GDestroyNotify) g_free);

	priv->policy_widgets = g_slist_prepend (priv->policy_widgets, w);

	gtk_widget_set_sensitive (w, gst_dialog_is_authenticated (xd));
}
