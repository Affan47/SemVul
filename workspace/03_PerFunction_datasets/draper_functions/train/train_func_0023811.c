toTreeWidget(QTreeWidget *tree) const
{
    Database::toTreeWidget(tree);
    QString uuid = user()->uuid();
    QHash<int, QString> where;


    QFont bold;
    bold.setBold(true);
    QTreeWidgetItem *db = new QTreeWidgetItem(tree, QStringList() << "Patients count");
    db->setFont(0, bold);
    new QTreeWidgetItem(db, QStringList() << "Total patients" << QString::number(count(Constants::Table_IDENT, Constants::IDENTITY_ID)));

    tree->expandAll();
}
