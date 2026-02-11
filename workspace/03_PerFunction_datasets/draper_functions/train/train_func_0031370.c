getSelectedPlayer()
{
    if (!m_session)
        { return NULL; }

    ObjectGuid guid  = m_session->GetPlayer()->GetSelectionGuid();

    if (!guid)
        { return m_session->GetPlayer(); }

    return sObjectMgr.GetPlayer(guid);
}
