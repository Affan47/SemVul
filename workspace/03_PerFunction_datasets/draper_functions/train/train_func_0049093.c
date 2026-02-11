select(const FieldList &select, const JoinList &joins) const
{
    FieldList get;
    JoinList jns;
    QString fields, from;
    QStringList tables;

    for(int i=0; i < select.count(); ++i) {
        get << select.at(i);
        if (get.at(i).tableName.isEmpty() || get.at(i).fieldName.isEmpty()) {
            get[i].tableName = table(select.at(i).table);
            get[i].fieldName = fieldName(select.at(i).table, select.at(i).field);
        }
    }
    for(int i=0; i < joins.count(); ++i) {
        Field f1 = field(joins.at(i).field1.table, joins.at(i).field1.field);
        Field f2 = field(joins.at(i).field2.table, joins.at(i).field2.field);
        jns << Join(f1, f2);
    }


    for(int i=0; i < get.count(); ++i) {
        fields += QString("`%1`.`%2`, ").arg(get.at(i).tableName).arg(get.at(i).fieldName);
        tables << get.at(i).tableName;
    }
    tables.removeDuplicates();

    if (fields.isEmpty())
        return QString();
    fields.chop(2);


    QString j;
    for(int i=0; i < jns.count(); ++i) {
        j += joinToSql(jns.at(i)) + "\n";
        tables.removeAll(jns.at(i).field1.tableName);
    }
    tables.removeDuplicates();


    foreach(const QString &tab, tables) {
        from += QString("`%1`, ").arg(tab);
    }
    from.chop(2);

    return QString("SELECT %1 FROM %2 \n %3").arg(fields, from, j);
}
