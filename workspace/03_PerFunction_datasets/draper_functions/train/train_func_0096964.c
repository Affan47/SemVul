HandleBuybackItem(WorldPacket& recv_data)
{
    DEBUG_LOG("WORLD: Received opcode CMSG_BUYBACK_ITEM");
    ObjectGuid vendorGuid;
    uint32 slot;

    recv_data >> vendorGuid >> slot;

    Creature* pCreature = GetPlayer()->GetNPCIfCanInteractWith(vendorGuid, UNIT_NPC_FLAG_VENDOR);
    if (!pCreature)
    {
        DEBUG_LOG("WORLD: HandleBuybackItem - %s not found or you can't interact with him.", vendorGuid.GetString().c_str());
        _player->SendSellError(SELL_ERR_CANT_FIND_VENDOR, NULL, ObjectGuid(), 0);
        return;
    }


    if (GetPlayer()->hasUnitState(UNIT_STAT_DIED))
        { GetPlayer()->RemoveSpellsCausingAura(SPELL_AURA_FEIGN_DEATH); }

    Item* pItem = _player->GetItemFromBuyBackSlot(slot);
    if (pItem)
    {
        uint32 price = _player->GetUInt32Value(PLAYER_FIELD_BUYBACK_PRICE_1 + slot - BUYBACK_SLOT_START);
        if (_player->GetMoney() < price)
        {
            _player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, pItem->GetEntry(), 0);
            return;
        }

        ItemPosCountVec dest;
        InventoryResult msg = _player->CanStoreItem(NULL_BAG, NULL_SLOT, dest, pItem, false);
        if (msg == EQUIP_ERR_OK)
        {
            _player->ModifyMoney(-(int32)price);
            _player->RemoveItemFromBuyBackSlot(slot, false);
            _player->ItemAddedQuestCheck(pItem->GetEntry(), pItem->GetCount());
            _player->StoreItem(dest, pItem, true);
        }
        else
            { _player->SendEquipError(msg, pItem, NULL); }
        return;
    }
    else
        { _player->SendBuyError(BUY_ERR_CANT_FIND_ITEM, pCreature, 0, 0); }
}
