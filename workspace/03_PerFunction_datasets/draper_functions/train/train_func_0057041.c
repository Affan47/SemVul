addItem()
{
    QAbstractItemModel *model = mCombo->model();
    if (!model)
        return;

    if(!model->insertRow(model->rowCount()))
        LOG_ERROR("Unable to add row " + QString::number(mCombo->currentIndex()));


    mCombo->setCurrentIndex(model->rowCount()-1);
    mRemoveButton->setEnabled(true);


    Q_EMIT itemAdded(model->index(model->rowCount()-1, 0));
}
