insertRows(int row, int count, const QModelIndex &parent)
{

    if (d->m_ReadOnly)
        return false;

    Internal::TreeItem *parentItem = 0;
    if (!parent.isValid())
        parentItem = d->m_RootItem;
    else
        parentItem = d->getItem(parent);


    QHash<int, QVariant> hashData;
    hashData.insert(Constants::Data_Label, tr("New"));
    hashData.insert(Constants::Data_ParentId, parentItem->data(Constants::Data_Id));
    hashData.insert(Constants::Data_CreationDate, QDateTime::currentDateTime());
    hashData.insert(Constants::Data_IsTemplate, false);
    d->allInstancesBeginInsertRows(parent, row, row+count-1);
    for(int i=0; i<count; ++i) {
        Internal::TreeItem *item = new Internal::TreeItem(hashData, parentItem);
        if (!parentItem->insertChild(row+i, item))
            return false;
    }
    d->allInstancesEndInsertRows();
    return true;
}
