getAlertPackDescription(const QString &uuid)
{
    AlertPackDescription pack;
    pack.setData(AlertPackDescription::Uuid, uuid);
    if (!connectDatabase(Constants::DB_NAME, __LINE__))
        return pack;

    if (WarnMemberNames)
        qWarning() << "AlertBase::getAlertPackDescription";

    database().transaction();
    QHash<int, QString> where;
    where.insert(Constants::ALERT_PACKS_UID, QString("='%1'").arg(uuid));
    QSqlQuery query(database());
    if (query.exec(select(Constants::Table_ALERT_PACKS, where))) {
        if (query.next()) {
            pack.setDbData(ItemId, query.value(Constants::ALERT_PACKS_ID));
            pack.setData(AlertPackDescription::Uuid, query.value(Constants::ALERT_PACKS_UID));
            pack.setData(AlertPackDescription::Validity, query.value(Constants::ALERT_PACKS_ISVALID));
            pack.setData(AlertPackDescription::InUse, query.value(Constants::ALERT_PACKS_IN_USE));
            pack.setDbData(LabelLID, query.value(Constants::ALERT_PACKS_LABEL_LID));
            pack.setDbData(CategoryLID, query.value(Constants::ALERT_PACKS_CATEGORY_LID));
            pack.setDbData(DescrLID, query.value(Constants::ALERT_PACKS_DESCRIPTION_LID));
            pack.setData(AlertPackDescription::Author, query.value(Constants::ALERT_PACKS_AUTHORS));
            pack.setData(AlertPackDescription::Vendor, query.value(Constants::ALERT_PACKS_VENDOR));
            pack.setData(AlertPackDescription::WebLink, query.value(Constants::ALERT_PACKS_URL));
            pack.setData(AlertPackDescription::GeneralIcon, query.value(Constants::ALERT_PACKS_THEMEDICON));
            pack.setData(AlertPackDescription::Version, query.value(Constants::ALERT_PACKS_VERSION));
            pack.setData(AlertPackDescription::FreeMedFormsCompatVersion, query.value(Constants::ALERT_PACKS_FMFVERSION));
            pack.setData(AlertPackDescription::CreationDate, query.value(Constants::ALERT_PACKS_CREATEDATE));
            pack.setData(AlertPackDescription::LastModificationDate, query.value(Constants::ALERT_PACKS_LASTUPDATE));

        }
    } else {
        LOG_QUERY_ERROR(query);
        query.finish();
        database().rollback();
        return pack;
    }

    if (!getAlertPackLabels(pack)) {
        database().rollback();
        return pack;
    }
    database().commit();
    return pack;
}
