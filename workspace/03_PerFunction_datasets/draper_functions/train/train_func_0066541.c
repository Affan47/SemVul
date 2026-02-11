tableRemoveRow()
{
    QTextCursor cursor = textEdit()->textCursor();
    QTextTable *table = cursor.currentTable();
    if (!table)
        return;
    int col = 0;
    int row = 0;
    int nrows, ncols;
    if (cursor.hasSelection()) {
        cursor.selectedTableCells(&row, &nrows, &col, &ncols);
        if (nrows == 0)
            nrows++;
    } else {
        QTextTableCell cell = table->cellAt(cursor);
        row = cell.row();
        nrows = 1;
    }
    table->removeRows(row , nrows);
}
