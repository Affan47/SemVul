go_locale_sel_set_sensitive (GOLocaleSel *ls, gboolean sensitive)
{
	g_return_if_fail (GO_IS_LOCALE_SEL (ls));

	gtk_widget_set_sensitive (GTK_WIDGET (ls->locales), sensitive);
}
