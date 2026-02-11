cb_realize (GtkWindow *toplevel, WBCGtk *wbcg)
{
	GtkAllocation ta;

	g_return_if_fail (GTK_IS_WINDOW (toplevel));

	gtk_widget_get_allocation (GTK_WIDGET (toplevel), &ta);
	gtk_window_set_default_size (toplevel, ta.width, ta.height);


	if (wbcg->snotebook) {
		wbcg_focus_cur_scg (wbcg);
		wbcg_update_menu_feedback (wbcg, wbcg_cur_sheet (wbcg));
	}
}
