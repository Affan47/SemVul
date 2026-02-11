regular_row_pos(int y, struct fpga_model* model)
{
	int row_pos = pos_in_row(y, model);
	if (row_pos == -1 || row_pos == HCLK_POS) return -1;
	if (row_pos > HCLK_POS) row_pos--;
	return row_pos;
}
