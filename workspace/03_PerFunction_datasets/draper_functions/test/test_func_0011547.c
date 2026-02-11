badDropSelection()
{
    QList<QTreeWidgetItem*> items = selectedItems();
    QList<QTreeWidgetItem*> children;
    QTreeWidgetItem* parent;
    int t=0;
    foreach (QTreeWidgetItem* item, items)
    {
        if (indexOfTopLevelItem(item)<0)
        {
                children.append(item);
                parent = children.at(0)->parent();

                for (int i=0; i < children.count(); i++)
                {
                    if (children.at(i)->parent() != parent)
                        return true;
                }
        }
        else    t++;

        if (t > 0 && children.count() > 0)
            return true;
    }
    return false;
}
