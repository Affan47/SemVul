set_buttons_sensisitivity_according_to_scheme (GeditPreferencesDialog *dlg,
					       const gchar            *scheme_id)
{
	gboolean editable;

	editable = ((scheme_id != NULL) && is_gedit_user_style_scheme (scheme_id));

	gtk_widget_set_sensitive (dlg->priv->uninstall_scheme_button,
				  editable);
}
