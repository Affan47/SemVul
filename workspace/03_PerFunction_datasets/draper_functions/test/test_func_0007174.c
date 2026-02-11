analysis_tool_calc_length (analysis_tools_data_generic_t *info)
{
	int           result = 1;
	GSList        *dataset;

	for (dataset = info->input; dataset; dataset = dataset->next) {
		GnmValue    *current = dataset->data;
		int      given_length;

		if (info->group_by == GROUPED_BY_AREA) {
			given_length = (current->v_range.cell.b.row - current->v_range.cell.a.row + 1) *
				(current->v_range.cell.b.col - current->v_range.cell.a.col + 1);
		} else
			given_length = (info->group_by == GROUPED_BY_COL) ?
				(current->v_range.cell.b.row - current->v_range.cell.a.row + 1) :
				(current->v_range.cell.b.col - current->v_range.cell.a.col + 1);
		if (given_length > result)
			result = given_length;
	}
	if (info->labels)
		result--;
	return result;
}
