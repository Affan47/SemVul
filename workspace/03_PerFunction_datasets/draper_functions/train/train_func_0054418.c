enableAllChildren(bool enable, QStandardItem *item)
{
    item->setEnabled(enable);
    for(int i=0; i < item->rowCount(); i++) {
        QStandardItem *childItem = item->child(i);
        enableAllChildren(enable, childItem);
    }
}
