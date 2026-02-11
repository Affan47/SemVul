getAllLabels(const QVariant &SID, const int libelleFieldLang)
{
    if (!database().isOpen()) {
        if (!database().open()) {
            LOG_ERROR(tkTr(Trans::Constants::UNABLE_TO_OPEN_DATABASE_1_ERROR_2).arg(Constants::DB_NAME).arg(database().lastError().text()));
            return QStringList();
        }
    }
    QSqlQuery query(database());
    QHash<int, QString> where;
    QString req;

    int field = libelleFieldLang;
    if (libelleFieldLang==-1) {
        field = getLibelleLanguageField();
    }


    where.insert(Constants::LIBELLE_SID, QString("=%1").arg(SID.toInt()));
    req = select(Constants::Table_Libelle, field, where);
    QStringList toReturn;
    if (query.exec(req)) {
        while (query.next()) {
            toReturn << query.value(0).toString();
        }
    } else {
        LOG_QUERY_ERROR(query);
    }
    return toReturn;
}
