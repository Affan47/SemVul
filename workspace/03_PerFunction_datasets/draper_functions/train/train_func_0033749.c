results_switch_to_page(results_t * r)
{
	GtkTreeSelection *selection = gtk_tree_view_get_selection(r->summary_view);
	GtkTreeIter iter;
	gboolean sens = FALSE;
	if (gtk_tree_selection_get_selected(selection, NULL, &iter)) {
		int f;
		result_item_t *item;
		results_sort_e sort;
		results_sort_dir_e dir;
		gtk_tree_model_get(GTK_TREE_MODEL(r->summary_tree), &iter, RESULTS_SUMMARY_COLUMN_FORM, &f,
				   RESULTS_SUMMARY_COLUMN_ITEM, &item, -1);
		poldiff_form_e form = (poldiff_form_e) f;
		if (item != NULL && result_item_get_current_sort(item, form, &sort, &dir)) {
			sens = TRUE;
		}
	}
	toplevel_set_sort_menu_sensitivity(r->top, sens);
}
