loadData()
{
    m_ui.m_lwLevelSets->clear();

    QStringList fileList = KGlobal::dirs()->findAllResources("appdata", "levels/*.dat", KStandardDirs::NoDuplicates);

    LevelSet ls;
    foreach (const QString& fileName, fileList)
    {
        ls.loadFromFile(fileName);
        QString visibleName = ls.visibleName();
        if (!visibleName.isEmpty())
        {
            QListWidgetItem* item = new QListWidgetItem;
            item->setIcon(KIcon( QLatin1String( "katomic" )));
            item->setText(visibleName);
            item->setData(KAtomic::LevelSetNameRole, ls.name());
            item->setData(KAtomic::LevelSetDescriptionRole, ls.description());
            item->setData(KAtomic::LevelSetAuthorRole, ls.author());
            item->setData(KAtomic::LevelSetAuthorEmailRole, ls.authorEmail());
            item->setData(KAtomic::LevelSetLevelCountRole, ls.levelCount());
            m_ui.m_lwLevelSets->addItem(item);
        }
    }


    if(!m_gameCurrentLevelSetName.isEmpty())
        setCurrentLevelSet(m_gameCurrentLevelSetName);
}
