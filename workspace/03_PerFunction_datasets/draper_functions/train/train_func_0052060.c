e_selection_model_simple_set_row_count (ESelectionModelSimple *esms,
                                        gint row_count)
{
	if (esms->row_count != row_count) {
		ESelectionModelArray *esma = E_SELECTION_MODEL_ARRAY (esms);
		if (esma->eba)
			g_object_unref (esma->eba);
		esma->eba = NULL;
		esma->selected_row = -1;
		esma->selected_range_end = -1;
	}

	esms->row_count = row_count;
}
