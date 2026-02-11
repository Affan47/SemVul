saveEpisodeModifications(Internal::EpisodeData *episode)
{
    if (!episode->isModified())
        return false;
    QSqlDatabase DB = QSqlDatabase::database(DB_NAME);
    if (!connectDatabase(DB, __LINE__)) {
        return false;
    }


    QSqlQuery query(DB);
    QHash<int, QString> where;

    for(int i = 0; i < episode->modifications().count(); ++i) {
        EpisodeModificationData &m = episode->modifications()[i];
        if (!m.isModified())
            continue;
        where.clear();
        if (m.modificationId()!=-1) {

            where.insert(EP_MODIF_ID, QString("=%1").arg(m.modificationId()));
            query.prepare(prepareUpdateQuery(Table_EPISODES_MODIF,
                                             QList<int>()
                                             << EP_MODIF_DATE
                                             << EP_MODIF_USERUID
                                             << EP_MODIF_TRACE
                                             , where));
            query.bindValue(0, m.data(EpisodeModificationData::Date));
            query.bindValue(1, m.data(EpisodeModificationData::UserUid));
            query.bindValue(2, m.data(EpisodeModificationData::Trace));
            if (!query.exec()) {
                LOG_QUERY_ERROR(query);
                return false;
            } else {
                m.setModified(false);
            }
        } else {

            query.prepare(prepareInsertQuery(Table_EPISODES_MODIF));
            query.bindValue(EP_MODIF_ID, QVariant());
            query.bindValue(EP_MODIF_EPISODE_ID, m.data(EpisodeModificationData::EpisodeId));
            query.bindValue(EP_MODIF_USERUID, m.data(EpisodeModificationData::UserUid));
            query.bindValue(EP_MODIF_DATE, m.data(EpisodeModificationData::Date));
            query.bindValue(EP_MODIF_TRACE, m.data(EpisodeModificationData::Trace));
            if (!query.exec()) {
                LOG_QUERY_ERROR(query);
                return false;
            } else {
                m.setData(EpisodeModificationData::ModificationId, query.lastInsertId());
                m.setModified(false);
            }
        }
    }
    return true;
}
