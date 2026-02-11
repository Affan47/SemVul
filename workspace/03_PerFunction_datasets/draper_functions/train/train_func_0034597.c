HandleRaidTargetUpdateOpcode(WorldPacket& recv_data)
{
    uint8  x;
    recv_data >> x;

    Group* group = GetPlayer()->GetGroup();
    if (!group)
        return;


    if (x == 0xFF)
    {
        group->SendTargetIconList(this);
    }
    else
    {
        if (group->isRaidGroup() &&
                !group->IsLeader(GetPlayer()->GetObjectGuid()) &&
                !group->IsAssistant(GetPlayer()->GetObjectGuid()))
            return;

        ObjectGuid guid;
        recv_data >> guid;
        group->SetTargetIcon(x, _player->GetObjectGuid(), guid);
    }
}
