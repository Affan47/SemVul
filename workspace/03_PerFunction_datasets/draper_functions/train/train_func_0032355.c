gotAllGroups()
{
    if (!m_oldConfig1) {
        logFileError() << "AllGroups without previous File specification" << endl;
        return;
    }

    const QStringList allGroups = m_oldConfig1->groupList();
    for (QStringList::ConstIterator it = allGroups.begin();
            it != allGroups.end(); ++it) {
        m_oldGroup = QStringList() << *it;
        m_newGroup = m_oldGroup;
        gotAllKeys();
    }
}
