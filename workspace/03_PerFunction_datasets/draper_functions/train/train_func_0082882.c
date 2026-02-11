populateWithPatientData()
{

    if (!m_Widget->numberWithControlKey().isEmpty())
        return;
    if (patient()->uuid().isEmpty()) {
        m_Widget->clear();
        return;
    }

    QString fullNumber;
    fullNumber.fill(' ', 13);


    if (patient()->data(Core::IPatient::Gender).toString()=="M") {
        fullNumber[0] = '1';
    } else if (patient()->data(Core::IPatient::Gender).toString()=="F") {
        fullNumber[0] = '2';
    }


    QModelIndex idx = patient()->index(patient()->currentPatientIndex().row(), Core::IPatient::DateOfBirth);
    QDate birth = patient()->data(idx, Qt::EditRole).toDate();
    if (birth.isValid()) {

        fullNumber = fullNumber.left(1) + QString::number(birth.year()).right(2) + fullNumber.mid(3);

        QString month = QString::number(birth.month());
        if (month.size()==1)
            month.prepend("0");
        fullNumber = fullNumber.left(3) + month + fullNumber.mid(5);
    }

    fullNumber = fullNumber.simplified();
    m_Widget->setNumberWithoutControlKey(fullNumber);

}
