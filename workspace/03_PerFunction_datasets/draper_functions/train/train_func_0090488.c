BroadcastPacket(WorldPacket* packet, bool ignorePlayersInBGRaid, int group, ObjectGuid ignore)
{
    for (GroupReference* itr = GetFirstMember(); itr != NULL; itr = itr->next())
    {
        Player* pl = itr->getSource();
        if (!pl || (ignore && pl->GetObjectGuid() == ignore) || (ignorePlayersInBGRaid && pl->GetGroup() != this))
            { continue; }

        if (pl->GetSession() && (group == -1 || itr->getSubGroup() == group))
            { pl->GetSession()->SendPacket(packet); }
    }
}
