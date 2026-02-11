HandleAddFriendOpcodeCallBack(QueryResult* result, uint32 accountId, std::string friendNote)
{
    if (!result)
        return;

    uint32 friendLowGuid = (*result)[0].GetUInt32();
    ObjectGuid friendGuid = ObjectGuid(HIGHGUID_PLAYER, friendLowGuid);
    Team team = Player::TeamForRace((*result)[1].GetUInt8());

    delete result;

    WorldSession* session = sWorld.FindSession(accountId);
    if (!session || !session->GetPlayer())
        return;

    FriendsResult friendResult = FRIEND_NOT_FOUND;
    if (friendGuid)
    {
        if (friendGuid == session->GetPlayer()->GetObjectGuid())
            friendResult = FRIEND_SELF;
        else if (session->GetPlayer()->GetTeam() != team && !sWorld.getConfig(CONFIG_BOOL_ALLOW_TWO_SIDE_ADD_FRIEND) && session->GetSecurity() < SEC_MODERATOR)
            friendResult = FRIEND_ENEMY;
        else if (session->GetPlayer()->GetSocial()->HasFriend(friendGuid))
            friendResult = FRIEND_ALREADY;
        else
        {
            Player* pFriend = ObjectAccessor::FindPlayer(friendGuid);
            if (pFriend && pFriend->IsInWorld() && pFriend->IsVisibleGloballyFor(session->GetPlayer()))
                friendResult = FRIEND_ADDED_ONLINE;
            else
                friendResult = FRIEND_ADDED_OFFLINE;

            if (!session->GetPlayer()->GetSocial()->AddToSocialList(friendGuid, false))
            {
                friendResult = FRIEND_LIST_FULL;
                DEBUG_LOG("WORLD: %s's friend list is full.", session->GetPlayer()->GetName());
            }

            session->GetPlayer()->GetSocial()->SetFriendNote(friendGuid, friendNote);
        }
    }

    sSocialMgr.SendFriendStatus(session->GetPlayer(), friendResult, friendGuid, false);

    DEBUG_LOG("WORLD: Sent (SMSG_FRIEND_STATUS)");
}
