gui_clear_block(row1, col1, row2, col2)
    int	    row1;
    int	    col1;
    int	    row2;
    int	    col2;
{

    clip_may_clear_selection(row1, row2);

    gui_mch_clear_block(row1, col1, row2, col2);


    if (       gui.cursor_row >= row1 && gui.cursor_row <= row2
	    && gui.cursor_col >= col1 && gui.cursor_col <= col2)
	gui.cursor_is_valid = FALSE;
}
