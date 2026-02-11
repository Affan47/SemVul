HandleAutoEquipItemSlotOpcode(WorldPacket& recv_data)
{
    ObjectGuid itemGuid;
    uint8 dstslot;
    recv_data >> itemGuid >> dstslot;


    if (!Player::IsEquipmentPos(INVENTORY_SLOT_BAG_0, dstslot))
        { return; }

    Item* item = _player->GetItemByGuid(itemGuid);
    uint16 dstpos = dstslot | (INVENTORY_SLOT_BAG_0 << 8);

    if (!item || item->GetPos() == dstpos)
        { return; }

    _player->SwapItem(item->GetPos(), dstpos);
}
