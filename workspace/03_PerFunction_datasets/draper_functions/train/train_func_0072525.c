HandleChannelDeathItem(bool apply, bool Real)
{
    if (Real && !apply)
    {
        if (m_removeMode != AURA_REMOVE_BY_DEATH)
            { return; }

        if (m_modifier.m_amount <= 0)
            { return; }

        SpellEntry const* spellInfo = GetSpellProto();
        if (spellInfo->EffectItemType[m_effIndex] == 0)
            { return; }

        Unit* victim = GetTarget();
        Unit* caster = GetCaster();
        if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
            { return; }


        if (spellInfo->EffectItemType[m_effIndex] == 6265)
        {

            if (!((Player*)caster)->isHonorOrXPTarget(victim) ||
                (victim->GetTypeId() == TYPEID_UNIT && !((Player*)caster)->isAllowedToLoot((Creature*)victim)))
                { return; }
        }


        uint32 noSpaceForCount = 0;
        uint32 count = m_modifier.m_amount;

        ItemPosCountVec dest;
        InventoryResult msg = ((Player*)caster)->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, spellInfo->EffectItemType[m_effIndex], count, &noSpaceForCount);
        if (msg != EQUIP_ERR_OK)
        {
            count -= noSpaceForCount;
            ((Player*)caster)->SendEquipError(msg, NULL, NULL, spellInfo->EffectItemType[m_effIndex]);
            if (count == 0)
                { return; }
        }

        Item* newitem = ((Player*)caster)->StoreNewItem(dest, spellInfo->EffectItemType[m_effIndex], true);
        ((Player*)caster)->SendNewItem(newitem, count, true, true);
    }
}
