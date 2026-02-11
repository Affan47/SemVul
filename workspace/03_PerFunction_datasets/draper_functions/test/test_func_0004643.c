btn_buttonsheet_build(MainInfo *min, ButtonInfo *bti, const gchar *label, gboolean partial, GCallback func, gpointer user)
{
	GtkWidget	*sheet = NULL;
	GList		*iter;

	if(label == NULL)
		label = BTN_DEFAULT_SHEET;
	if(func == NULL)
		func = G_CALLBACK(evt_button_clicked);
	if(user == NULL)
		user = min;
	for(iter = bti->sheets; iter != NULL; iter = g_list_next(iter))
	{
		if(strcmp(((ButtonSheet *) iter->data)->label, label) == 0)
		{
			sheet = buttonsheet_build(min, iter->data, partial, func, user);
			break;
		}
	}
	return sheet;
}
