gui_delete_lines(row, count)
    int	    row;
    int	    count;
{
    if (count <= 0)
	return;

    if (row + count > gui.scroll_region_bot)

	gui_clear_block(row, gui.scroll_region_left,
			      gui.scroll_region_bot, gui.scroll_region_right);
    else
    {
	gui_mch_delete_lines(row, count);


	if (gui.cursor_row >= row
		&& gui.cursor_col >= gui.scroll_region_left
		&& gui.cursor_col <= gui.scroll_region_right)
	{
	    if (gui.cursor_row < row + count)
		gui.cursor_is_valid = FALSE;
	    else if (gui.cursor_row <= gui.scroll_region_bot)
		gui.cursor_row -= count;
	}
    }
}
