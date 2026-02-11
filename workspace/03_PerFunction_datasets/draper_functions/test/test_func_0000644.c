EquippedOk(Player* pPlayer, uint32 spellId)
{
    SpellEntry const* spell = GetSpellStore()->LookupEntry(spellId);

    if (!spell)
    {
        return false;
    }

    for (int i = 0; i < 3; ++i)
    {
        uint32 reqSpell = spell->EffectTriggerSpell[i];
        if (!reqSpell)
        {
            continue;
        }

        Item* pItem;
        for (int j = EQUIPMENT_SLOT_START; j < EQUIPMENT_SLOT_END; ++j)
        {
            pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, j);
            if (pItem)
                if (pItem->GetProto()->RequiredSpell == reqSpell)
                {

                    debug_log("SD2: player attempt to unlearn spell %u, but item %u is equipped.", reqSpell, pItem->GetProto()->ItemId);
                    return false;
                }
        }
    }
    return true;
}
