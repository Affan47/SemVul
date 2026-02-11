keyPressEvent(QKeyEvent* event)
{
    QTreeWidgetItem *item = currentItem();
    if (item && ((event->key() == Qt::Key_Return) ||
                 (event->key() == Qt::Key_Space)))
    {
        TraceCall* c = ((CallItem*) item)->call();
        CostItem* f = _showCallers ? c->caller(false) : c->called(false);

        TraceItemView::activated(f);
    }
    QTreeView::keyPressEvent(event);
}
