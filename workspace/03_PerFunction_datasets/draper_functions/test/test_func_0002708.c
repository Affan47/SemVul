prefs_set_toggle(PrefParam *pparam)
{
	cm_return_if_fail(pparam->type == P_BOOL);
	cm_return_if_fail(*pparam->widget != NULL);

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(*pparam->widget),
				     *((gboolean *)pparam->data));
}
