setCurrentLevelSet(const QString& levelSetName)
{
    m_gameCurrentLevelSetName = levelSetName;

    int count = m_ui.m_lwLevelSets->count();
    for (int i=0;i<count;++i)
    {
        QListWidgetItem* item = m_ui.m_lwLevelSets->item(i);
        if (!item)
            continue;

        if (item->data(KAtomic::LevelSetNameRole).toString() == levelSetName)
        {
            m_ui.m_lwLevelSets->setCurrentItem(item);
            break;
        }
    }
}
