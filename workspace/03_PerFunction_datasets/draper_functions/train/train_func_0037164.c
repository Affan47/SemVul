Create(ObjectGuid guid, const char* text)
{
    std::string escapedText = text;
    CharacterDatabase.escape_string(escapedText);
    CharacterDatabase.BeginTransaction();

    CharacterDatabase.DirectPExecute("INSERT INTO character_ticket "
                                     "(guid, ticket_text) "
                                     "VALUES "
                                     "(%u,   '%s')",
                                     guid.GetCounter(), escapedText.c_str());


    QueryResult* result = CharacterDatabase.PQuery("SELECT ticket_id, guid, resolved "
                                                   "FROM character_ticket "
                                                   "WHERE guid = %u AND resolved = 0;",
                                                   guid.GetCounter());

    CharacterDatabase.CommitTransaction();

    if (!result)
        return;

    Field* fields = result->Fetch();
    uint32 ticketId = fields[0].GetUInt32();


    GMTicket& ticket = m_GMTicketMap[guid];
    if (ticket.GetPlayerGuid())
        m_GMTicketListByCreatingOrder.remove(&ticket);


    ticket.Init(guid, text, "", time(NULL), ticketId);
    m_GMTicketListByCreatingOrder.push_back(&ticket);
}
