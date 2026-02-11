getLabelFromLid(const QVariant &LID)
{
    int lid = LID.toInt();
    if (d->m_CachedSystemLabelsFromLid.keys().contains(lid)) {
        return *d->m_CachedSystemLabelsFromLid[lid];
    }
    if (!database().isOpen()) {
        if (!database().open()) {
            LOG_ERROR(tkTr(Trans::Constants::UNABLE_TO_OPEN_DATABASE_1_ERROR_2).arg(Constants::DB_NAME).arg(database().lastError().text()));
            return QString();
        }
    }
    QSqlQuery query(database());
    QHash<int, QString> where;
    where.insert(Constants::LIBELLE_LID, QString("=%1").arg(LID.toString()));
    QString req = select(Constants::Table_Libelle, getLibelleLanguageField(), where);
    if (query.exec(req)) {
        if (query.next()) {
            QString *s = new QString(query.value(0).toString());
            d->m_CachedSystemLabelsFromLid.insert(lid, s);
            return *s;
        }
    } else {
        LOG_QUERY_ERROR(query);
    }
    return QString();
}
