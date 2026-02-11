markAllDosageTransmitted(const QStringList &dosageUuids)
{
    if (dosageUuids.count()==0)
        return true;
    QSqlDatabase DB = database();
    if (!connectDatabase(DB, __FILE__, __LINE__))
        return false;

    QStringList reqs;
    foreach(const QString &s, dosageUuids) {
        QString req = QString("UPDATE `DOSAGE` SET `TRANSMITTED`='%1' WHERE %2")
                      .arg(QDateTime::currentDateTime().toString(Qt::ISODate))
                      .arg(QString("`POSO_UUID`='%1'").arg(s));
        reqs << req;
    }
    if (!executeSQL(reqs,DB)) {
        LOG_ERROR(tr("Unable to update the protocol's transmission date."));
        return false;
    }
    return true;
}
