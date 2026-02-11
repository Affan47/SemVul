prepareUpdateQuery(const int tableref, const QList<int> &fieldref, const QHash<int, QString> &conditions)
{
    QString toReturn;
    QString tmp;
    foreach(const int &i, fieldref) {
        tmp += "`" + fieldName(tableref, i) + "`= ?, ";
    }
    tmp.chop(2);
    toReturn = QString("UPDATE `%1` SET %2 WHERE %4")
               .arg(table(tableref))
               .arg(tmp)
               .arg(getWhereClause(tableref, conditions));


    if (WarnSqlCommands)
        qWarning() << toReturn;
    return toReturn;
}
