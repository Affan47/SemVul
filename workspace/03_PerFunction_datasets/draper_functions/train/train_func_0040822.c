addItem()
{


    if ( !d->servNewButton || !d->servNewButton->isEnabled() )
        return;

    QModelIndex currentIndex = d->selectedIndex();

    const QString& currentTextLE=d->lineEdit->text();
    bool alreadyInList(false);

    if (!d->checkAtEntering)
    {

        if ( currentIndex.isValid() ) {
          if ( d->model->data( currentIndex, Qt::DisplayRole ).toString() == currentTextLE )
            alreadyInList = true;
        }
        else
        {
            alreadyInList = d->model->stringList().contains( currentTextLE, Qt::CaseSensitive );
        }
    }
    if ( d->servNewButton )
        d->servNewButton->setEnabled(false);

    bool block = d->lineEdit->signalsBlocked();
    d->lineEdit->blockSignals(true);
    d->lineEdit->clear();
    d->lineEdit->blockSignals(block);

    d->listView->selectionModel()->setCurrentIndex(currentIndex, QItemSelectionModel::Deselect);

    if (!alreadyInList)
    {
        block = d->listView->signalsBlocked();

        if ( currentIndex.isValid() ) {
          d->model->setData(currentIndex, currentTextLE );
        } else {
            QStringList lst;
            lst<<currentTextLE;
            lst<<d->model->stringList();
            d->model->setStringList(lst);
        }
        emit changed();
        emit added( currentTextLE );
    }

    d->updateButtonState();
}
