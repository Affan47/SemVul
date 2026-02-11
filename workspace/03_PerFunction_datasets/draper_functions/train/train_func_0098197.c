BroadcastToOfficers(WorldSession* session, const std::string& msg, uint32 language)
{
    if (session && session->GetPlayer() && HasRankRight(session->GetPlayer()->GetRank(), GR_RIGHT_OFFCHATSPEAK))
    {
        for (MemberList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
        {
            WorldPacket data;
            ChatHandler::FillMessageData(&data, session, CHAT_MSG_OFFICER, language, msg.c_str());

            Player* pl = ObjectAccessor::FindPlayer(ObjectGuid(HIGHGUID_PLAYER, itr->first));

            if (pl && pl->GetSession() && HasRankRight(pl->GetRank(), GR_RIGHT_OFFCHATLISTEN) && !pl->GetSocial()->HasIgnore(session->GetPlayer()->GetObjectGuid()))
                pl->GetSession()->SendPacket(&data);
        }
    }
}
