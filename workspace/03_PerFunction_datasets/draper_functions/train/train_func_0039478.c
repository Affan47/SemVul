gtk_term_save(GtkWidget *widget, gchar *filename)
{
	GtkTerm	*term;
	gchar *file;

	g_return_val_if_fail (widget != NULL,0);
	g_return_val_if_fail (GTK_IS_TERM (widget),0);

	term = GTK_TERM (widget);

	if (filename)
		file = filename;
	else
		file = term->name->str;

	if (!e_save(term->a,file)) return 0;

	if (filename) g_string_assign(term->name,filename);
	term->changed = 0;
	g_signal_emit(GTK_OBJECT(term),gtk_term_signals[GTK_TERM_SAVED],0);

	return 1;
}
