refresh()
{
    clear();
    setColumnWidth(1, _eventType2 ? 50:0);

    if (_eventType) {
        headerItem()->setText(0, _eventType->name());
        headerItem()->setText(1, tr("%1 per call").arg(_eventType->name()));
    }
    if (_eventType2) {
        headerItem()->setText(2, _eventType2->name());
        headerItem()->setText(3, tr("%1 per call").arg(_eventType2->name()));
    }

    if (!_data || !_activeItem) return;

    TraceFunction* f = activeFunction();
    if (!f) return;


    TraceCallList l = _showCallers ? f->callers(true) : f->callings(true);

    QList<QTreeWidgetItem*> items;
    foreach(TraceCall* call, l)
	if (call->subCost(_eventType)>0)
            items.append(new CallItem(this, 0, call));


    setSortingEnabled(false);
    addTopLevelItems(items);
    setSortingEnabled(true);

    header()->setSortIndicatorShown(false);

    header()->resizeSections(QHeaderView::ResizeToContents);

    if (!_eventType2) {
        setColumnWidth(2, 0);
        setColumnWidth(3, 0);
    }
}
