on_menu_project_activate (GtkWidget *widget, void *user) {


    if (g_active_editor == NULL) {
		gtk_widget_set_tooltip_text (GTK_WIDGET
					 (gui->menugui->menu_projcreate),
					_("This function requires an active document"));
		return;
	}

    if (!gummi_project_active()) {
        gtk_widget_set_sensitive (GTK_WIDGET
                                 (gui->menugui->menu_projopen), TRUE);

        if (g_active_editor->filename != NULL) {
            gtk_widget_set_sensitive (GTK_WIDGET
                                 (gui->menugui->menu_projcreate), TRUE);
        }
        else {
			gtk_widget_set_tooltip_text (GTK_WIDGET
					 (gui->menugui->menu_projcreate),
					_("This function requires the current\n"
					  "active document to be saved. "));
		}
    }
    else {
        gtk_widget_set_sensitive (GTK_WIDGET
                                 (gui->menugui->menu_projclose), TRUE);
    }
}
