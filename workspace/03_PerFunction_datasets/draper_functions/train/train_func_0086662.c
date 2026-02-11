isTooPrecise(int row, int column)
{
    if (row < 0 || column < 0) return false;

    RideFile::SeriesType what = model->columnType(column);
    int dp;
    QString value = QString("%1").arg(getValue(row, column), 0, 'g', 10);

    if ((dp = value.indexOf(".")) >= 0)
        if (value.length()-(dp+1) > RideFile::decimalsFor(what)) return true;

    return false;
}
