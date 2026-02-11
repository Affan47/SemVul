usermenu_destroy (GtkWidget * menu)
{
	GList *items = ((GtkMenuShell *) menu)->children;
	GList *next;

	while (items)
	{
		next = items->next;
		gtk_widget_destroy (items->data);
		items = next;
	}
}
