headerClicked(int col)
{
    if (col == 0) {
        sortByColumn(col, Qt::AscendingOrder);
    }

    else if (col <4) {
        sortByColumn(col, Qt::DescendingOrder);
    }
}
