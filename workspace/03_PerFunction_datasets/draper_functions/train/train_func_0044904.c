_e2_about_dialog_tabchange_cb (GtkNotebook *notebook,
	GtkNotebookPage *page, guint page_num, E2_Sextet *dialog_data)
{
	switch (page_num)
	{
		case 1:
			dialog_data->d = dialog_data->a;
			gtk_widget_show (dialog_data->f);
			break;
		case 2:
			dialog_data->d = dialog_data->b;
			gtk_widget_show (dialog_data->f);
			break;
		case 3:
			dialog_data->d = dialog_data->c;
			gtk_widget_show (dialog_data->f);
			break;
		default:

			gtk_widget_hide (dialog_data->f);
			break;
	}
}
