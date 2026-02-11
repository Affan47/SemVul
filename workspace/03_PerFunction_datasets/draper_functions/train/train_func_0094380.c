IsSpellValid(SpellEntry const* spellInfo, Player* pl, bool msg)
{

    if (!spellInfo)
        { return false; }

    bool need_check_reagents = false;


    for (int i = 0; i < MAX_EFFECT_INDEX; ++i)
    {
        switch (spellInfo->Effect[i])
        {
            case SPELL_EFFECT_NONE:
                continue;


            case SPELL_EFFECT_CREATE_ITEM:
            {
                if (!ObjectMgr::GetItemPrototype(spellInfo->EffectItemType[i]))
                {
                    if (msg)
                    {
                        if (pl)
                            { ChatHandler(pl).PSendSysMessage("Craft spell %u create item (Entry: %u) but item does not exist in item_template.", spellInfo->Id, spellInfo->EffectItemType[i]); }
                        else
                            { sLog.outErrorDb("Craft spell %u create item (Entry: %u) but item does not exist in item_template.", spellInfo->Id, spellInfo->EffectItemType[i]); }
                    }
                    return false;
                }

                need_check_reagents = true;
                break;
            }
            case SPELL_EFFECT_LEARN_SPELL:
            {
                SpellEntry const* spellInfo2 = sSpellStore.LookupEntry(spellInfo->EffectTriggerSpell[i]);
                if (!IsSpellValid(spellInfo2, pl, msg))
                {
                    if (msg)
                    {
                        if (pl)
                            { ChatHandler(pl).PSendSysMessage("Spell %u learn to broken spell %u, and then...", spellInfo->Id, spellInfo->EffectTriggerSpell[i]); }
                        else
                            { sLog.outErrorDb("Spell %u learn to invalid spell %u, and then...", spellInfo->Id, spellInfo->EffectTriggerSpell[i]); }
                    }
                    return false;
                }
                break;
            }
        }
    }

    if (need_check_reagents)
    {
        for (int j = 0; j < MAX_SPELL_REAGENTS; ++j)
        {
            if (spellInfo->Reagent[j] > 0 && !ObjectMgr::GetItemPrototype(spellInfo->Reagent[j]))
            {
                if (msg)
                {
                    if (pl)
                        { ChatHandler(pl).PSendSysMessage("Craft spell %u requires reagent item (Entry: %u) but item does not exist in item_template.", spellInfo->Id, spellInfo->Reagent[j]); }
                    else
                        { sLog.outErrorDb("Craft spell %u requires reagent item (Entry: %u) but item does not exist in item_template.", spellInfo->Id, spellInfo->Reagent[j]); }
                }
                return false;
            }
        }
    }

    return true;
}
