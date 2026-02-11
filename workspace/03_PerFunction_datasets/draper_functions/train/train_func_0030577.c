addAvailability()
{
    if (!m_Mapper)
        return;
    if (!m_AvailabilityModel)
        return;
    AvailabilityEditDialog dlg(this);
    const QModelIndex &index= ui->availabilityView->currentIndex();
    if (index.isValid())
        dlg.setDayOfWeek(index.data(WeekDayRole).toInt());
    if (dlg.exec() == QDialog::Accepted) {

        const QList<DayAvailability> &av = dlg.getAvailabilities();
        for(int i = 0 ; i < av.count(); ++i) {
            m_AvailabilityModel->addAvailability(av.at(i));
        }

    }
}
