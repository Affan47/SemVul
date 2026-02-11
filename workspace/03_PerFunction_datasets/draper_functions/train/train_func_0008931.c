cb_sheet_visibility_change (Sheet *sheet,
			    G_GNUC_UNUSED GParamSpec *pspec,
			    SheetControlGUI *scg)
{
	gboolean viz;

	g_return_if_fail (IS_SHEET_CONTROL_GUI (scg));

	viz = sheet_is_visible (sheet);
	gtk_widget_set_visible (GTK_WIDGET (scg->grid), viz);
	gtk_widget_set_visible (GTK_WIDGET (scg->label), viz);

	wbcg_menu_state_sheet_count (scg->wbcg);
}
