newEventAtAvailabity(const QModelIndex &index)
{
    QModelIndex idx = index;
    if (!index.isValid()) {

        idx = d->m_AvailModel->index(0,0);
        idx = d->m_AvailModel->index(0,0, idx);
    }
    Calendar::BasicItemEditorDialog dlg(d->m_CalendarItemModel, this);
    QDateTime start = d->m_AvailModel->itemFromIndex(idx)->data().toDateTime();
    if (start.isNull())
        return;


    Calendar::CalendarItem item = d->m_CalendarItemModel->insertItem(start, start.addSecs((d->ui->availDurationCombo->currentIndex()+1)*5*60));
    dlg.init(item);
    if (dlg.exec() != QDialog::Accepted) {
        d->m_CalendarItemModel->removeItem(item.uid());
    }
    recalculateAvailabilitiesWithDurationIndex(d->ui->availDurationCombo->currentIndex());
}
