setFormTreeModel(FormTreeModel *model)
{
    if (!model)
        return;
    if (d->_formTreeModel==model)
        return;

    if (d->_formTreeModel) {
        disconnect(d->ui->formView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(currentSelectedFormChanged(QModelIndex, QModelIndex)));
        disconnect(d->_formTreeModel, SIGNAL(modelReset()), this, SLOT(onFormTreeModelReset()));
    }
    d->_formTreeModel = model;

    d->ui->formView->setModel(d->_formTreeModel);
    d->_delegate->setFormTreeModel(d->_formTreeModel);

    onFormTreeModelReset();
    connect(d->_formTreeModel, SIGNAL(modelReset()), this, SLOT(onFormTreeModelReset()));
    connect(d->ui->formView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(currentSelectedFormChanged(QModelIndex, QModelIndex)));
    Q_EMIT actionsEnabledStateChanged();
}
