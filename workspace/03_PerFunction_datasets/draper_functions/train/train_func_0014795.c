done(int r)
{

    drugNameButton->setFocus();

    disconnect(drugModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),
             this, SLOT(updatePosologicSentence(QModelIndex,QModelIndex)));

    dosageViewer->commitToModel();

    if (r == QDialog::Accepted) {
        dosageViewer->done(r);
    }
    QDialog::done(r);
}
