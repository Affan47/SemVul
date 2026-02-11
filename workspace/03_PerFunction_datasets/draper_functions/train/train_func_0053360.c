add_value_or_special (data_analysis_output_t *dao, int col, int row,
		      gnm_float x)
{
	if (gnm_finite (x))
		dao_set_cell_float (dao, col, row, x);
	else {
		dao_set_cell (dao, col, row, "-");
		dao_set_align (dao, col, row, col, row,
			       GNM_HALIGN_CENTER, GNM_VALIGN_TOP);
	}
}
