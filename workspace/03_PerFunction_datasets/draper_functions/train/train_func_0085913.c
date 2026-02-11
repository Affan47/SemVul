identity_view (gboolean visible)
{
	if (visible) {
		gtk_widget_show (get("username"));
		gtk_widget_show (get("username_entry"));
		gtk_widget_show (get("password"));
		gtk_widget_show (get("password_entry"));
	}
	else {
		gtk_widget_hide (get("username"));
		gtk_widget_hide (get("username_entry"));
		gtk_widget_hide (get("password"));
		gtk_widget_hide (get("password_entry"));
	}
}
