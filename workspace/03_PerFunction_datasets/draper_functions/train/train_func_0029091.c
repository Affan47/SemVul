DoCreateItem(SpellEffectIndex eff_idx, uint32 itemtype)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        { return; }

    Player* player = (Player*)unitTarget;

    uint32 newitemid = itemtype;
    ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(newitemid);
    if (!pProto)
    {
        player->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
        return;
    }


    uint32 bgType = 0;
    switch (m_spellInfo->Id)
    {
        case SPELL_AV_MARK_WINNER:
        case SPELL_AV_MARK_LOSER:
            bgType = BATTLEGROUND_AV;
            break;
        case SPELL_WS_MARK_WINNER:
        case SPELL_WS_MARK_LOSER:
            bgType = BATTLEGROUND_WS;
            break;
        case SPELL_AB_MARK_WINNER:
        case SPELL_AB_MARK_LOSER:
            bgType = BATTLEGROUND_AB;
            break;
        default:
            break;
    }

    uint32 num_to_add = damage;

    if (num_to_add < 1)
        { num_to_add = 1; }
    if (num_to_add > pProto->Stackable)
        { num_to_add = pProto->Stackable; }


    int items_count = 1;


    num_to_add *= items_count;


    ItemPosCountVec dest;
    uint32 no_space = 0;
    InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, newitemid, num_to_add, &no_space);
    if (msg != EQUIP_ERR_OK)
    {

        if (msg == EQUIP_ERR_INVENTORY_FULL || msg == EQUIP_ERR_CANT_CARRY_MORE_OF_THIS)
            { num_to_add -= no_space; }
        else
        {

            player->SendEquipError(msg, NULL, NULL, newitemid);
            return;
        }
    }

    if (num_to_add)
    {

        Item* pItem = player->StoreNewItem(dest, newitemid, true, Item::GenerateItemRandomPropertyId(newitemid));


        if (!pItem)
        {
            player->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
            return;
        }


        if (pItem->GetProto()->Class != ITEM_CLASS_CONSUMABLE && pItem->GetProto()->Class != ITEM_CLASS_QUEST)
            { pItem->SetGuidValue(ITEM_FIELD_CREATOR, player->GetObjectGuid()); }


        player->SendNewItem(pItem, num_to_add, true, !bgType);


        if (!bgType)
            { player->UpdateCraftSkill(m_spellInfo->Id); }
    }


    if (no_space > 0 && bgType)
    {
        if (BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(BattleGroundTypeId(bgType)))
            { bg->SendRewardMarkByMail(player, newitemid, no_space); }
    }
}
