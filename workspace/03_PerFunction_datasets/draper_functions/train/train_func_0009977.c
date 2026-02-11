setModel(QAbstractItemModel* m)
{
    QTreeView::setModel(m);
    d->modified = false;

    QItemSelectionModel* selectionmodel = new QItemSelectionModel(m, this);
    setSelectionModel(selectionmodel);

    connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(slotSelectionChanged()));
    connect(m, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(slotDataChanged(QModelIndex,QModelIndex)));
}
