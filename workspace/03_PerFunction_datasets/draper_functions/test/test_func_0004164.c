getNumberOfEpisodes(const QString &formUid, const QStringList &equivalents)
{

    Utils::FieldList uuid;
    uuid << Utils::Field(Constants::Table_EPISODES, Constants::EPISODES_FORM_PAGE_UID, QString("='%1'").arg(formUid));
    if (!equivalents.isEmpty()) {
        foreach(const QString &eq, equivalents)
            uuid << Utils::Field(Constants::Table_EPISODES, Constants::EPISODES_FORM_PAGE_UID, QString("='%1'").arg(eq));
    }


    QHash<int, QString> where;
    where.insert(Constants::EPISODES_ISVALID, "=1");
    where.insert(Constants::EPISODES_PATIENT_UID, QString("='%1'").arg(patient()->uuid()));

    QString filter = getWhereClause(Constants::Table_EPISODES, where).remove("WHERE") +
            " AND (" + getWhereClause(uuid, Utils::Database::OR) + ")";
    return count(Constants::Table_EPISODES, Constants::EPISODES_ID, filter);
}
