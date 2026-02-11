HandleAutoBankItemOpcode(WorldPacket& recvPacket)
{
    DEBUG_LOG("WORLD: CMSG_AUTOBANK_ITEM");
    uint8 srcbag, srcslot;

    recvPacket >> srcbag >> srcslot;
    DEBUG_LOG("STORAGE: receive srcbag = %u, srcslot = %u", srcbag, srcslot);

    Item* pItem = _player->GetItemByPos(srcbag, srcslot);
    if (!pItem)
        { return; }

    ItemPosCountVec dest;
    InventoryResult msg = _player->CanBankItem(NULL_BAG, NULL_SLOT, dest, pItem, false);
    if (msg != EQUIP_ERR_OK)
    {
        _player->SendEquipError(msg, pItem, NULL);
        return;
    }


    if (dest.size() == 1 && dest[0].pos == pItem->GetPos())
    {

        _player->SendEquipError(EQUIP_ERR_NONE, pItem, NULL);
        return;
    }

    _player->RemoveItem(srcbag, srcslot, true);
    _player->BankItem(dest, pItem, true);
}
