enableDisable(QTreeWidget *tree)
{

    for (int i=0; i< tree->invisibleRootItem()->childCount(); i++) {
        QTreeWidgetItem *item = tree->invisibleRootItem()->child(i);


        bool enable = (dynamic_cast<QComboBox*>(tree->itemWidget(item,0))->currentIndex() != 0);


        tree->itemWidget(item,2)->setEnabled(enable);
        tree->itemWidget(item,3)->setEnabled(enable);
    }
}
