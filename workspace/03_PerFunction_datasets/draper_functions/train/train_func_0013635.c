getFormLabels(const QVariant &drugId, const QString &lang)
{
    QStringList toReturn;
    QSqlDatabase DB = QSqlDatabase::database(Constants::DB_DRUGS_NAME);
    if (!connectDatabase(DB, __FILE__, __LINE__))
        return toReturn;


    QString l = lang;
    if (l.isEmpty()) {
        l = Trans::Constants::ALL_LANGUAGE;
    }
    Utils::FieldList get;
    get << Utils::Field(Constants::Table_LABELS, Constants::LABELS_LABEL);
    Utils::FieldList cond;
    cond << Utils::Field(Constants::Table_DRUG_FORMS, Constants::DRUG_FORMS_DID, QString("='%1'").arg(drugId.toString()));
    cond << Utils::Field(Constants::Table_LABELS, Constants::LABELS_LANG, QString("='%1'").arg(l));
    Utils::JoinList joins;
    joins << Utils::Join(Constants::Table_DRUG_FORMS, Constants::DRUG_FORMS_MASTERLID, Constants::Table_LABELSLINK, Constants::LABELSLINK_MASTERLID);
    joins << Utils::Join(Constants::Table_LABELSLINK, Constants::LABELSLINK_LID, Constants::Table_LABELS, Constants::LABELS_LID);
    QString req = select(get, joins, cond);
    QSqlQuery query(req, DB);
    if (query.isActive()) {
        while (query.next()) {
            const QString &form = query.value(0).toString();
            if (!form.isEmpty())
                toReturn << form;
        }
    } else {
        LOG_QUERY_ERROR(query);
    }
    return toReturn;
}
