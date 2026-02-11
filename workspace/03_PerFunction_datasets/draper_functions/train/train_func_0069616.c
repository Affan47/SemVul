getAllLabels(const int masterLid)
    {
        Utils::JoinList joins;
        joins << Utils::Join(Constants::Table_LABELS, Constants::LABELS_LID, Constants::Table_LABELSLINK, Constants::LABELSLINK_LID);
        Utils::FieldList cond;
        cond << Utils::Field(Constants::Table_LABELSLINK, Constants::LABELSLINK_MASTERLID, QString("=%1").arg(masterLid));

        QHash<QString, QString> toReturn;
        QString req = q->select(Constants::Table_LABELS, joins, cond);
        QSqlQuery query(QSqlDatabase::database(Constants::DB_DRUGS_NAME));
        if (query.exec(req)) {
            while (query.next()) {
                toReturn.insert(query.value(Constants::LABELS_LANG).toString(), query.value(Constants::LABELS_LABEL).toString());
            }
        } else {
            LOG_QUERY_ERROR_FOR(q, query);
        }
        return toReturn;
    }
