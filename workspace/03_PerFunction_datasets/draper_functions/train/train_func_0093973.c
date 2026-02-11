moleculeName() const
{
    if (!m_levelData || !m_levelData->molecule())
    {
        kDebug() << "level or molecule data is null!";
        return QString();
    }

    return m_levelData->molecule()->moleculeName();
}
