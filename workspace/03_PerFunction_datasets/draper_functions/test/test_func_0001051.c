sheet_widget_radio_button_finalize (GObject *obj)
{
	SheetWidgetRadioButton *swrb = GNM_SOW_RADIO_BUTTON (obj);

	g_return_if_fail (swrb != NULL);

	g_free (swrb->label);
	swrb->label = NULL;
	value_release (swrb->value);
	swrb->value = NULL;

	dependent_set_expr (&swrb->dep, NULL);

	sheet_object_widget_class->finalize (obj);
}
