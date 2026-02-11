analysis_tools_write_a_label (GnmValue *val, data_analysis_output_t *dao,
			      gboolean   labels, group_by_t group_by,
			      int x, int y)
{
	if (labels) {
		GnmValue *label = value_dup (val);

		label->v_range.cell.b = label->v_range.cell.a;
		dao_set_cell_expr (dao, x, y, gnm_expr_new_constant (label));
		analysis_tools_remove_label (val, labels, group_by);
	} else {
		char const *str = ((group_by == GROUPED_BY_ROW) ? "row" : "col");
		char const *label = ((group_by == GROUPED_BY_ROW) ? _("Row") : _("Column"));

		GnmFunc *fd_concatenate;
		GnmFunc *fd_cell;

		fd_concatenate = gnm_func_lookup_or_add_placeholder ("CONCATENATE");
		gnm_func_ref (fd_concatenate);
		fd_cell = gnm_func_lookup_or_add_placeholder ("CELL");
		gnm_func_ref (fd_cell);

		dao_set_cell_expr (dao, x, y, gnm_expr_new_funcall3
				   (fd_concatenate, gnm_expr_new_constant (value_new_string (label)),
				    gnm_expr_new_constant (value_new_string (" ")),
				    gnm_expr_new_funcall2 (fd_cell,
							   gnm_expr_new_constant (value_new_string (str)),
							   gnm_expr_new_constant (value_dup (val)))));

		gnm_func_unref (fd_concatenate);
		gnm_func_unref (fd_cell);
	}
}
