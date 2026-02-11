findOrMakeItem(QTreeWidgetItem *parent, const QString &name)
{
    for (int i = 0; i < parent->childCount(); i++) {
        QTreeWidgetItem *child = parent->child(i);
        if (child->text(0) == name)
            return child;
    }
    QTreeWidgetItem *ret = new QTreeWidgetItem(parent, NonActionItem);
    ret->setText(0, name);
    ui.list->expandItem(ret);
    ret->setFlags(ret->flags() & ~Qt::ItemIsSelectable);
    return ret;
}
