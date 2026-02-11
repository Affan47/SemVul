onPackCategoriesChanged(const QModelIndex &index, const QModelIndex &)
{
    if (!index.isValid())
        return;

    const QString &vendor = d->m_PackCategoriesModel->vendor(index);
    const QList<Pack::DataType> &type = d->m_PackCategoriesModel->datatype(index);
    d->m_PackModel->filter(vendor, type);

    d->ui->packName->clear();
    d->ui->packSummary->clear();

    d->ui->packView->setCurrentIndex(d->m_PackModel->index(0,0));
    d->ui->packView->selectionModel()->select(d->m_PackModel->index(0,0), QItemSelectionModel::SelectCurrent);
    onPackIndexActivated(d->m_PackModel->index(0,0), QModelIndex());
}
