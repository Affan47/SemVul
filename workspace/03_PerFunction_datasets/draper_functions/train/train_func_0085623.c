saveItemRelations(AlertItem &item)
{

    if (!connectDatabase(Constants::DB_NAME, __LINE__))
        return false;

    if (WarnMemberNames)
        qWarning() << "AlertBase::saveItemRelations";


    if (item.relations().count()==0)
        return true;
    int id = -1;
    if (!item.db(RelatedId).isValid() || item.db(RelatedId).toInt() <= 0) {
        id = max(Constants::Table_ALERT_RELATED, Constants::ALERT_RELATED_REL_ID).toInt() + 1;
        item.setDb(RelatedId, id);
    } else {
        id = item.db(RelatedId).toInt();
    }

    QSqlQuery query(database());
    for(int i=0; i<item.relations().count(); ++i) {
        AlertRelation &rel = item.relationAt(i);
        if (rel.id()==-1) {

            QString req = prepareInsertQuery(Constants::Table_ALERT_RELATED);
            query.prepare(req);
            query.bindValue(Constants::ALERT_RELATED_ID, QVariant());
            query.bindValue(Constants::ALERT_RELATED_REL_ID, id);
            query.bindValue(Constants::ALERT_RELATED_RELATED_TO, rel.relatedTo());
            query.bindValue(Constants::ALERT_RELATED_RELATED_UID, rel.relatedToUid());
            if (query.exec()) {
                rel.setId(query.lastInsertId().toInt());
            } else {
                LOG_QUERY_ERROR(query);
                return false;
            }
            query.finish();
        } else {

            if (rel.isModified()) {
                QHash<int, QString> where;
                where.insert(Constants::ALERT_RELATED_ID, QString("=%1").arg(rel.id()));
                QString req = prepareUpdateQuery(Constants::Table_ALERT_RELATED, QList<int>()
                                                 << Constants::ALERT_RELATED_RELATED_TO
                                                 << Constants::ALERT_RELATED_RELATED_UID,
                                                 where);
                query.prepare(req);
                int i = 0;
                query.bindValue(i, rel.relatedTo());
                query.bindValue(++i, rel.relatedToUid());
                if (query.exec()) {
                    rel.setModified(false);
                } else {
                    LOG_QUERY_ERROR(query);
                    return false;
                }
            }
        }
    }
    return true;
}
