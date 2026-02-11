gtk_term_is_initialized(GtkWidget *widget)
{
	GtkTerm	*term;

	g_return_val_if_fail (widget != NULL,0);
	g_return_val_if_fail (GTK_IS_TERM (widget),0);

	term = GTK_TERM (widget);

	return !term->initializing;
}
