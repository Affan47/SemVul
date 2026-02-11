validate (EAPMethod *parent)
{
	GtkWidget *widget;
	GtkTreeModel *model;
	GtkTreeIter iter;
	EAPMethod *eap = NULL;
	const char *file;
	gboolean provisioning;
	gboolean valid = FALSE;

	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_fast_pac_provision_checkbutton"));
	g_assert (widget);
	provisioning = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget));
	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_fast_pac_file_button"));
	g_assert (widget);
	file = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (widget));
	if (!provisioning && !file)
		return FALSE;

	widget = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_fast_inner_auth_combo"));
	g_assert (widget);
	model = gtk_combo_box_get_model (GTK_COMBO_BOX (widget));
	gtk_combo_box_get_active_iter (GTK_COMBO_BOX (widget), &iter);
	gtk_tree_model_get (model, &iter, I_METHOD_COLUMN, &eap, -1);
	g_assert (eap);
	valid = eap_method_validate (eap);
	eap_method_unref (eap);
	return valid;
}
