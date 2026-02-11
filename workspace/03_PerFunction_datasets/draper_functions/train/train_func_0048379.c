sheet_widget_checkbox_init_full (SheetWidgetCheckbox *swc,
				 GnmCellRef const *ref, char const *label)
{
	static int counter = 0;

	g_return_if_fail (swc != NULL);

	swc->label = label ? g_strdup (label) : g_strdup_printf (_("CheckBox %d"), ++counter);
	swc->being_updated = FALSE;
	swc->value = FALSE;
	swc->dep.sheet = NULL;
	swc->dep.flags = checkbox_get_dep_type ();
	swc->dep.texpr = (ref != NULL)
		? gnm_expr_top_new (gnm_expr_new_cellref (ref))
		: NULL;
}
