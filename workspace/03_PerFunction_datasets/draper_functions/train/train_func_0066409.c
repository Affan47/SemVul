enable_controls
	(
	)
	{

	gtk_widget_set_sensitive(remove_btn, cur_pal >= 0 &&
					palettes.size() > 1);
	if (cur_pal == -1)
		{
		gtk_widget_set_sensitive(down_btn, false);
		gtk_widget_set_sensitive(up_btn, false);
		gtk_widget_set_sensitive(remove_btn, false);
		}
	else
		{
		gtk_widget_set_sensitive(down_btn,
					cur_pal < palettes.size() - 1);
		gtk_widget_set_sensitive(up_btn, cur_pal > 0);
		gtk_widget_set_sensitive(remove_btn, palettes.size() > 1);
		}
	}
