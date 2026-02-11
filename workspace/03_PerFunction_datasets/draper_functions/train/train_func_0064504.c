event_CheckToggled(GtkWidget * widget)
{
	UT_ASSERT(widget);

	tControl id = (tControl) GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget),
												 WIDGET_ID_TAG));

	gboolean state = gtk_toggle_button_get_active(
		GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(widget)));

	tCheckState cs;


	if (state == TRUE)
		cs = check_TRUE;
	else
		cs = check_FALSE;

	_setCheckItemValue(id, cs);
}
