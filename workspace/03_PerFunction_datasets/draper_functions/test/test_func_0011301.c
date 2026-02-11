slotLinkClicked(const QString & url)
{
    Q_UNUSED(url)
    QModelIndex index = focusedIndex();
    Q_ASSERT(index.isValid());

    const QSortFilterProxyModel * model = qobject_cast<const QSortFilterProxyModel*>(index.model());
    const ItemsModel * realmodel = qobject_cast<const ItemsModel*>(model->sourceModel());
    KNS::Entry * entry = realmodel->entryForIndex(model->mapToSource(index));
    emit performAction(DownloadDialog::kContactEmail, entry);
}
