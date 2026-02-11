gui_cli_result(char *s)
{
	char *o;
	float p;
	GtkStyle *style;
	style = gtk_widget_get_style(cmdtextbox);
	gtk_text_freeze(GTK_TEXT(cmdtextbox));
	o = gtk_editable_get_chars(GTK_EDITABLE(cmdtextbox), 0, -1);
	gtk_editable_delete_text(GTK_EDITABLE(cmdtextbox), 0, -1);
	gtk_text_insert(GTK_TEXT(cmdtextbox), clifont, &style->fg[GTK_STATE_INSENSITIVE], NULL, o, -1);
	gtk_text_insert(GTK_TEXT(cmdtextbox), clifont, &colors[3], NULL, lastcmd, -1);

	if (!s || !strlen(s))
		s = "        \n";
	gtk_text_insert(GTK_TEXT(cmdtextbox), clifont, NULL, NULL, "\n", -1);
	gtk_text_thaw(GTK_TEXT(cmdtextbox));
	p = GTK_TEXT(cmdtextbox)->vadj->upper;
	p -= (float)(cmdtextbox->allocation.height - 1.0);
	if (p < 0.0)
		p = 0.0;
	gtk_adjustment_set_value(GTK_TEXT(cmdtextbox)->vadj, p);
	gtk_text_insert(GTK_TEXT(cmdtextbox), clifont, NULL, NULL, s, -1);
	gtk_editable_set_position(GTK_EDITABLE(cmdtextbox), -1);
	g_free(o);
}
