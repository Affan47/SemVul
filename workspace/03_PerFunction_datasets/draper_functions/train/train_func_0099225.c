HandleInspectOpcode(WorldPacket& recv_data)
{
    ObjectGuid guid;
    recv_data >> guid;
    DEBUG_LOG("Inspected guid is %s", guid.GetString().c_str());

    _player->SetSelectionGuid(guid);

    Player* plr = sObjectMgr.GetPlayer(guid);
    if (!plr)
        return;

    WorldPacket data(SMSG_INSPECT_RESULTS, 50);
    data << plr->GetPackGUID();

    if (sWorld.getConfig(CONFIG_BOOL_TALENTS_INSPECTING) || _player->isGameMaster())
        plr->BuildPlayerTalentsInfoData(&data);
    else
    {
        data << uint32(0);
        data << uint8(0);
        data << uint8(0);
    }

    plr->BuildEnchantmentsInfoData(&data);

    SendPacket(&data);
}
