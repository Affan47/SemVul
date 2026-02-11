fillTreeWidget(QTreeWidget *tree) const
{

    tree->clear();
    tree->setColumnCount(2);
    QFont bold;
    bold.setBold(true);

    QTreeWidgetItem *general = new QTreeWidgetItem(tree, QStringList() << tkTr(Trans::Constants::INFORMATION));
    general->setFont(0, bold);
    new QTreeWidgetItem(general, QStringList() << "Uuid" << data(FormIODescription::UuidOrAbsPath).toString());
    new QTreeWidgetItem(general, QStringList() << tkTr(Trans::Constants::AUTHOR) << data(FormIODescription::Author).toString());
    new QTreeWidgetItem(general, QStringList() << tkTr(Trans::Constants::LICENSE) << data(FormIODescription::LicenseName).toString());
    new QTreeWidgetItem(general, QStringList() << tkTr(Trans::Constants::DESCRIPTION) << data(FormIODescription::ShortDescription).toString());
    new QTreeWidgetItem(general, QStringList() << QString("Extracted from database") << data(FormIODescription::FromDatabase).toString());

    QTreeWidgetItem *version = new QTreeWidgetItem(tree, QStringList() << tkTr(Trans::Constants::VERSION));
    version->setFont(0, bold);
    new QTreeWidgetItem(version, QStringList() << tkTr(Trans::Constants::VERSION) << data(FormIODescription::Version).toString());
    new QTreeWidgetItem(version, QStringList() << QCoreApplication::translate("Forms", "Creation date") << data(FormIODescription::CreationDate).toDate().toString(QLocale().dateFormat(QLocale::ShortFormat)));
    if (!data(FormIODescription::LastModificationDate).isNull())
        new QTreeWidgetItem(version, QStringList() << QCoreApplication::translate("Forms", "Last modification date") << data(FormIODescription::LastModificationDate).toDate().toString(QLocale().dateFormat(QLocale::ShortFormat)));

    tree->expandAll();
    tree->resizeColumnToContents(0);
    tree->resizeColumnToContents(1);
}
