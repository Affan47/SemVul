update_pm_widgets(GtkComboBox * optionmenu, gpointer userdata)
{
    GtkWidget *preferences_dialog = GTK_WIDGET(userdata);

    PanelApplet *applet = PANEL_APPLET(g_object_get_data(G_OBJECT(preferences_dialog),
                                                         "applet"));

    int selected_val = get_selected_manager(optionmenu);

    GtkEntry *command = GTK_ENTRY(g_object_get_data(G_OBJECT(preferences_dialog),
                                                    "package_manager_command"));
    GtkToggleButton *run_in_xterm = GTK_TOGGLE_BUTTON(g_object_get_data(G_OBJECT(preferences_dialog), "package_manager_run_in_xterm"));

    if (selected_val == -1) {


        gchar *customcmdkey = g_strdup_printf("%s/package_manager/custom_package_manager_command",
                                              panel_applet_get_preferences_key(applet));
        gchar *runxtermkey = g_strdup_printf("%s/package_manager/custom_package_manager_run_in_xterm",
                                             panel_applet_get_preferences_key(applet));

        GError *err = NULL;

        gchar *customstringval = gconf_client_get_string(confclient,
                                                         customcmdkey,
                                                         &err);

        if (err) {
            g_error_free(err);
            err = NULL;
        }

        if (customstringval)
            gtk_entry_set_text(command, customstringval);
        else
            gtk_entry_set_text(command, "");

        gtk_toggle_button_set_active(run_in_xterm, gconf_client_get_bool(confclient, runxtermkey, &err));

        if (err) {
            g_error_free(err);
            err = NULL;
        }

        gtk_widget_set_sensitive(GTK_WIDGET(command), 1);
        gtk_widget_set_sensitive(GTK_WIDGET(run_in_xterm), 1);

        g_free(customstringval);
        g_free(runxtermkey);
        g_free(customcmdkey);
    } else {
        const package_manager *pm = hardcoded_package_managers + selected_val;

        gtk_widget_set_sensitive(GTK_WIDGET(command), 0);
        gtk_widget_set_sensitive(GTK_WIDGET(run_in_xterm), 0);

        gtk_entry_set_text(command, pm->cmd.c_str());
        gtk_toggle_button_set_active(run_in_xterm, pm->run_in_xterm);
    }
}
