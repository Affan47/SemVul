smooth()
{
    QString xs = xsstring(currentCell.row, model->columnType(currentCell.column));


    double left = 0.0;
    double right = 0.0;
    if (currentCell.row > 0) left = getValue(currentCell.row-1, currentCell.column);
    if (currentCell.row < (ride->ride()->dataPoints().count()-1)) right = getValue(currentCell.row+1, currentCell.column);
    double value = (left+right) / 2;


    setModelValue(currentCell.row, currentCell.column, value);
}
