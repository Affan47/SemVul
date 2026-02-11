operator<(const QTreeWidgetItem &other) const
{
    const int column = treeWidget() ? treeWidget()->sortColumn() : 0;
    return KStringHandler::naturalCompare(text(column), other.text(column)) < 0;
}
