banlist_sensitize (banlist_info *banl)
{
	int checkable, i;


	checkable = banl->sess->me->op? banl->writeable: banl->readable;
	for (i = 0; i < MODE_CT; i++)
	{
		if (banl->checkboxes[i] == NULL)
			continue;
		if ((checkable & 1<<i) == 0)

		{
			gtk_widget_set_sensitive (banl->checkboxes[i], FALSE);
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (banl->checkboxes[i]), FALSE);
		}
		else

		{
			gtk_widget_set_sensitive (banl->checkboxes[i], TRUE);
		}
	}


	if (banl->sess->me->op == 0 || banl->line_ct == 0)
	{

		gtk_widget_set_sensitive (banl->but_clear, FALSE);
		gtk_widget_set_sensitive (banl->but_crop, FALSE);
		gtk_widget_set_sensitive (banl->but_remove, FALSE);
	}
	else
	{

		if (banl->select_ct == 0)
		{
			gtk_widget_set_sensitive (banl->but_clear, TRUE);
			gtk_widget_set_sensitive (banl->but_crop, FALSE);
			gtk_widget_set_sensitive (banl->but_remove, FALSE);
		}

		else
		{
			gtk_widget_set_sensitive (banl->but_clear, FALSE);
			gtk_widget_set_sensitive (banl->but_crop, TRUE);
			gtk_widget_set_sensitive (banl->but_remove, TRUE);
		}
	}


	gtk_widget_set_sensitive (banl->but_refresh, banl->pending? FALSE: banl->checked? TRUE: FALSE);
}
