select(const int &tableref, const QHash<int, QString> &conditions) const
{
    QString toReturn;
    QString tmp;
    QList<int> list = d_database->m_Tables_Fields.values(tableref);
    qSort(list);
    foreach(const int &i, list)
        tmp += "`" + table(tableref) + "`.`" + d_database->m_Fields.value(i) + "`, ";

    if (tmp.isEmpty())
        return QString::null;
    tmp.chop(2);
    toReturn = QString("SELECT %1 FROM `%2` WHERE %3")
            .arg(tmp)
            .arg(table(tableref))
            .arg(getWhereClause(tableref, conditions));
    if (WarnSqlCommands)
        qWarning() << toReturn;
    return toReturn;
}
