toTreeWidget(QTreeWidget *tree)
{
    QTreeWidgetItem *i = new QTreeWidgetItem(tree, QStringList() << tr("Form: ") + spec()->label());
    QFont bold;
    bold.setBold(true);
    i->setFont(0,bold);
    spec()->toTreeWidget(i);
    valueReferences()->toTreeWidget(i);
    scripts()->toTreeWidget(i);
    foreach(FormItem *c, formItemChildren()) {
        itemToTree(c, i);
    }
}
