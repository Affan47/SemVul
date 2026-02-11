activate(QString s)
{
    if (s.isEmpty())
        _listWidget->setCurrentRow(0);

    QString page = s;
    _activeSetting.clear();
    int p = s.indexOf("/");
    if (p>0) {
        page = s.left(p);
        _activeSetting = s.mid(p+1);
    }

    for(int row=0; row<_listWidget->count(); row++) {
        QListWidgetItem* i = _listWidget->item(row);
        if (i->text() != page) continue;

        if (_listWidget->currentRow() == row)

            listItemChanged(page);
        else
            _listWidget->setCurrentRow(row);
    }
}
