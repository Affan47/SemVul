removeItem()
{
    QAbstractItemModel *model = mCombo->model();
    if (model->rowCount() == minimumRowsAllowed)
        return;

    if (!model->removeRow(mCombo->currentIndex())) {
          LOG_ERROR("Unable to remove row " + QString::number(mCombo->currentIndex()));
    }

    const bool enabled = (model->rowCount() > 0);
    mRemoveButton->setEnabled(enabled);


    Q_EMIT itemRemoved();

}
