selection_start_colrow(int col, int row)
{
    int end_col;

    D_SELECT(("selection_start_colrow(%d, %d)\n", col, row));

    if (selection.op) {


        if (selection.beg.row < -TermWin.nscrolled)
            selection_reset();
        else
            selection_setclr(0, selection.beg.row, selection.beg.col, selection.end.row, selection.end.col);
    }
    selection.op = SELECTION_INIT;
    BOUND(row, 0, TERM_WINDOW_GET_REPORTED_ROWS() - 1);

    row -= TermWin.view_start;
    end_col = screen.text[row + TermWin.saveLines][TERM_WINDOW_GET_REPORTED_COLS()];
    if (end_col != WRAP_CHAR && col > end_col)
        col = TERM_WINDOW_GET_REPORTED_COLS();
    selection.mark.col = col;
    selection.mark.row = row;
}
