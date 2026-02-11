nma_mobile_wizard_present (NMAMobileWizard *self)
{
	g_return_if_fail (self != NULL);

	gtk_window_present (GTK_WINDOW (self->assistant));
	gtk_widget_show_all (self->assistant);
}
