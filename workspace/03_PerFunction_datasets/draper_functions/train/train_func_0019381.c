getAllDrugSourceInformation()
{
    QVector<DatabaseInfos *> infos;
    QString req = select(Constants::Table_SOURCES);
    QSqlQuery q(req, QSqlDatabase::database(Constants::DB_DRUGS_NAME));
    if (q.isActive()) {
        while (q.next()) {
            DatabaseInfos *info = new DatabaseInfos;
            info->sid = q.value(Constants::SOURCES_SID).toInt();
            info->version = q.value(Constants::SOURCES_VERSION).toString();
            info->names = d->getAllLabels(q.value(Constants::SOURCES_MASTERLID).toInt());
            info->identifier = q.value(Constants::SOURCES_DBUID).toString();
            info->compatVersion = q.value(Constants::SOURCES_FMFCOMPAT).toString();
            info->provider = q.value(Constants::SOURCES_PROVIDER).toString();
            info->weblink = q.value(Constants::SOURCES_WEBLINK).toString();
            info->author = q.value(Constants::SOURCES_AUTHORS).toString();
            info->license = q.value(Constants::SOURCES_COPYRIGHT).toString();

            info->date = q.value(Constants::SOURCES_DATE).toDate();
            info->drugsUidName = q.value(Constants::SOURCES_DRUGUID_NAME).toString();
            info->packUidName = q.value(Constants::SOURCES_PACKUID_NAME).toString();
            info->atcCompatible = q.value(Constants::SOURCES_ATC).toBool();
            info->iamCompatible = q.value(Constants::SOURCES_INTERACTIONS).toBool();
            info->authorComments = q.value(Constants::SOURCES_AUTHOR_COMMENTS).toString();
            info->lang_country = q.value(Constants::SOURCES_LANG).toString();
            info->setDrugsNameConstructor(q.value(Constants::SOURCES_DRUGNAMECONSTRUCTOR).toString());
            info->complementaryWebsite = q.value(Constants::SOURCES_COMPL_WEBSITE).toString();
            info->moleculeLinkCompletion = q.value(Constants::SOURCES_COMPLETION).toInt();

            if (QSqlDatabase::database(Constants::DB_DRUGS_NAME).driverName() == "QSQLITE") {
                info->fileName = databaseFileName();
            }
            infos << info;
        }
    } else {
        LOG_QUERY_ERROR(q);
    }
    return infos;
}
