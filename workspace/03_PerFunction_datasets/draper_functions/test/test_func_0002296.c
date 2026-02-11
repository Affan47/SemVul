ChangeMembersGroup(ObjectGuid guid, uint8 group)
{
    if (!isRaidGroup())
        { return; }

    Player* player = sObjectMgr.GetPlayer(guid);

    if (!player)
    {
        uint8 prevSubGroup = GetMemberGroup(guid);
        if (prevSubGroup == group)
            { return; }

        if (_setMembersGroup(guid, group))
        {
            SubGroupCounterDecrease(prevSubGroup);
            SendUpdate();
        }
    }
    else

        { ChangeMembersGroup(player, group); }
}
