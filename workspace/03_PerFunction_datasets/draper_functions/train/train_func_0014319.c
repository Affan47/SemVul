random_cor_tool_ok_clicked_cb (GtkWidget *button, RandomCorToolState *state)
{
	data_analysis_output_t  *dao;
	tools_data_random_cor_t  *data;
	gint err;

	data = g_new0 (tools_data_random_cor_t, 1);

	dao  = parse_output ((GenericToolState *)state, NULL);
	err = entry_to_int (GTK_ENTRY (state->count_entry), &data->count, FALSE);
	data->matrix = gnm_expr_entry_parse_as_value
		(GNM_EXPR_ENTRY (state->base.input_entry),
		 state->base.sheet);

	data->variables = data->matrix->v_range.cell.b.row -
		data->matrix->v_range.cell.a.row + 1;

	data->matrix_type = gnm_gui_group_value
		(state->base.gui, matrix_group);


	if (!cmd_analysis_tool (WORKBOOK_CONTROL (state->base.wbcg),
				state->base.sheet,
				dao, data, tool_random_cor_engine, TRUE) &&
	    (button == state->base.ok_button))
		gtk_widget_destroy (state->base.dialog);
}
