gpk_distro_upgrade_activate_cb (GApplication *application, GpkDistroUpgradePrivate *priv)
{
	PkControl *control;
	gboolean ret;
	const gchar *title = NULL;
	const gchar *message = NULL;
	GError *error = NULL;


	g_debug ("activated");
	gtk_widget_show (priv->assistant);


	control = pk_control_new ();
	ret = pk_control_get_properties (control, NULL, &error);
	if (!ret) {
		g_error ("Failed to contact PackageKit: %s", error->message);
		g_error_free (error);
		goto out;
	}


	title = _("Cannot perform operating system upgrade");


	g_object_get (control,
		      "roles", &priv->roles,
		      NULL);
	ret = pk_bitfield_contain (priv->roles, PK_ROLE_ENUM_GET_DISTRO_UPGRADES);
	if (ret) {
		ret = pk_bitfield_contain (priv->roles, PK_ROLE_ENUM_UPGRADE_SYSTEM);
		if (!ret) {

			message = _("Upgrading the operating system is not supported.");
		}
	} else {

		message = _("Cannot get operating system upgrade information.");
	}
	if (!ret) {
		GtkWidget *dialog;
		dialog = gtk_message_dialog_new (GTK_WINDOW (priv->assistant),
						 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_WARNING,
						 GTK_BUTTONS_CLOSE,
						 "%s", title);
		gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
							  "%s", message);
		g_signal_connect_swapped (dialog,
					  "response",
					  G_CALLBACK (g_application_release),
					  application);
		gtk_widget_show (dialog);
	}
out:
	return;
}
