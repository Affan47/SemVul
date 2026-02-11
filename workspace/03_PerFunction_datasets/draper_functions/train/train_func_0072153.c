tableMergeCells()
{
    if (!textEdit()->textCursor().hasSelection())
        return;
    QTextTable *table = textEdit()->textCursor().currentTable();
    if (!table)
        return;
    int col = 0;
    int row = 0;
    int nrows, ncols;
    textEdit()->textCursor().selectedTableCells(&row, &nrows, &col, &ncols);
    if ((nrows == 0) && (ncols == 0))
        return;
    table->mergeCells(textEdit()->textCursor());

    QTextTableCell cell = table->cellAt(row, col);
    textEdit()->setTextCursor(cell.firstCursorPosition());
}
