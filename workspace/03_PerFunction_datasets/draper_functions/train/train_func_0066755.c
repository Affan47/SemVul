dropEvent(QDropEvent* event)
{

    QTreeWidgetItem *item = currentItem();
    int idx1 = invisibleRootItem()->indexOfChild(item);
    int idx2 = indexAt(event->pos()).row();


    QTreeWidget::dropEvent(event);


    Q_EMIT itemMoved(item, idx1, idx2);
}
