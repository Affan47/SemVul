show_command_line_icon_release(
            GtkWidget *entry,
            GtkEntryIconPosition pos,
            GdkEvent *event,
            gpointer data)
{


	if ( pos == GTK_ENTRY_ICON_SECONDARY )
	{

		gtk_widget_hide(entry);
		gtk_entry_set_text(GTK_ENTRY(entry), "");
	}

	else if ( pos == GTK_ENTRY_ICON_PRIMARY )
	{

		gmpc_easy_command_help_window(gmpc_easy_command, NULL);

	}
}
