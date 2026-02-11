_Close(GMTicketStatus statusCode) const
{
    Player* pPlayer = sObjectMgr.GetPlayer(m_guid);
    if (!pPlayer)
        return;

    CharacterDatabase.PExecute("UPDATE character_ticket "
                               "SET resolved = 1 "
                               "WHERE guid = %u AND resolved = 0",
                               m_guid.GetCounter());

    if (statusCode != GM_TICKET_STATUS_DO_NOTHING)
        { pPlayer->GetSession()->SendGMTicketStatusUpdate(statusCode); }
}
