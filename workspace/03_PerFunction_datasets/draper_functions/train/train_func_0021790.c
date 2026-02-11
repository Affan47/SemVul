dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(column)
    if (d->m_ReadOnly)
        return false;

    if (WarnDragAndDrop)
        qWarning() << "TemplatesModel dropMimeData row" << row << "Action" << action << "parent" << parent.data().toString();

    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat(mimeTypes().at(0)))
        return false;

    QModelIndex parentIndex = parent;
    while (isTemplate(parentIndex)) {
        parentIndex = parentIndex.parent();
    }


    QList<QPersistentModelIndex> list = getIndexesFromMimeData(data);


    if  (action == Qt::MoveAction) {
        foreach(const QPersistentModelIndex &idx, list) {


            if (!reparentIndex(idx, parentIndex))
                return false;
        }
    } else if (action == Qt::CopyAction) {
        int parentId = d->getItem(parent)->id();
        foreach(const QPersistentModelIndex &idx, list) {
            int row = rowCount(parent);
            insertRow(row, parent);
            Internal::TreeItem *item = d->getItem(idx);
            Internal::TreeItem *newItem = d->getItem(index(row,0,parent));
            int id = newItem->id();
            newItem->replaceData(item->data());
            newItem->setData(Constants::Data_ParentId, parentId);
            newItem->setIsTemplate(item->isTemplate());
            newItem->setId(id);
        }
    }


    return true;
}
