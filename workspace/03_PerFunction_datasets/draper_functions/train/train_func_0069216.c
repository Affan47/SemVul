construct_consolidate (ConsolidateState *state, data_analysis_output_t  *dao)
{
	GnmConsolidate      *cs   = consolidate_new ();
	GnmConsolidateMode  mode = 0;
	char       const *func;
	GnmValue         *range_value;
	GtkTreeIter      iter;
	gboolean         has_iter;

	switch (gtk_combo_box_get_active (state->function)) {
	case 0 : func = "SUM"; break;
	case 1 : func = "MIN"; break;
	case 2 : func = "MAX"; break;
	case 3 : func = "AVERAGE"; break;
	case 4 : func = "COUNT"; break;
	case 5 : func = "PRODUCT"; break;
	case 6 : func = "STDEV"; break;
	case 7 : func = "STDEVP"; break;
	case 8 : func = "VAR"; break;
	case 9 : func = "VARP"; break;
	default :
		func = NULL;
		g_warning ("Unknown function index!");
	}

	consolidate_set_function (cs, gnm_func_lookup (func, NULL));

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (state->labels_row)))
		mode |= CONSOLIDATE_COL_LABELS;
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (state->labels_col)))
		mode |= CONSOLIDATE_ROW_LABELS;

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (state->labels_copy)))
		mode |= CONSOLIDATE_COPY_LABELS;
	if (!dao_put_formulas (dao))
		mode |= CONSOLIDATE_PUT_VALUES;

	consolidate_set_mode (cs, mode);

	g_return_val_if_fail (gtk_tree_model_iter_n_children
			      (state->source_areas,
			       NULL)> 2, NULL);

	has_iter = gtk_tree_model_get_iter_first (state->source_areas,
						  &iter);
	g_return_val_if_fail (has_iter, NULL);
	do {
		char *source;

		gtk_tree_model_get (state->source_areas,
				    &iter,
				    SOURCE_COLUMN, &source,
				    -1);
		if (strlen(source) != 0) {
			range_value = value_new_cellrange_str (state->base.sheet, source);

			if (range_value == NULL) {
				state->construct_error = g_strdup_printf (
					_("Specification %s "
					  "does not define a region"),
					source);
				g_free (source);
				consolidate_free (cs, FALSE);
				return NULL;
			}
			if (!consolidate_add_source (cs, range_value)) {
				state->construct_error = g_strdup_printf (
					_("Source region %s overlaps "
					  "with the destination region"),
					source);
				g_free (source);
				consolidate_free (cs, FALSE);
				return NULL;
			}
		}
		g_free (source);
	} while (gtk_tree_model_iter_next
		 (state->source_areas,&iter));

	return cs;
}
