setDrugId(const QVariant &drugId)
{
    if (drugId == m_UID)
        return true;
    m_UID = drugId;
    QString filter = QString("%1='%2'").arg(record().fieldName(Dosages::Constants::DrugUid_LK)).arg(m_UID.toString());

    int inn = -1;
    if (m_DrugsModel)
        inn = m_DrugsModel->drugData(drugId, Constants::Drug::MainInnCode).toInt();

    if (inn!=-1) {

        QString innFilter = QString::number(inn);
        innFilter = QString("%1=%2").arg(record().fieldName(Dosages::Constants::INN_LK)).arg(innFilter);

        innFilter = QString("(%1) AND (%2='%3')")
                    .arg(innFilter)
                    .arg(record().fieldName(Dosages::Constants::InnLinkedDosage))
                    .arg(m_DrugsModel->drugData(drugId, Constants::Drug::MainInnDosage).toString());
        filter = QString("((%1) OR (%2))").arg(filter).arg(innFilter);
    }

    if (WarnDebuggingData)
        LOG("DosageModel filter" + filter);

    setFilter(filter);
    select();
    return true;
}
