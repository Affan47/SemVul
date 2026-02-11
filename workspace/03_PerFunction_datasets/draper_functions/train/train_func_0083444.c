dropEvent(QDropEvent *event)
{
    QString name = event->mimeData()->data("application/x-columnchooser");

    if (name == "BikeScore?") name = QTextEdit("BikeScore&#8482;").toPlainText();
    tableView->setColumnHidden(logicalHeadings.indexOf(name), false);
    tableView->setColumnWidth(logicalHeadings.indexOf(name), 50);
    tableView->header()->moveSection(tableView->header()->visualIndex(logicalHeadings.indexOf(name)), 1);
    columnsChanged();
}
