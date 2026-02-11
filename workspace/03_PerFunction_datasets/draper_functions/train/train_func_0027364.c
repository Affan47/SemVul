SelectSpell(Unit* pTarget, int32 uiSchool, int32 iMechanic, SelectTarget selectTargets, uint32 uiPowerCostMin, uint32 uiPowerCostMax, float fRangeMin, float fRangeMax, SelectEffect selectEffects)
{

    if (!pTarget)
    {
        return false;
    }


    if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SILENCED))
    {
        return false;
    }


    SpellEntry const* apSpell[4];
    memset(apSpell, 0, sizeof(SpellEntry*) * 4);

    uint32 uiSpellCount = 0;

    SpellEntry const* pTempSpell;
    SpellRangeEntry const* pTempRange;


    for (uint8 i = 0; i < 4; ++i)
    {
        pTempSpell = GetSpellStore()->LookupEntry(m_creature->m_spells[i]);


        if (!pTempSpell)
        {
            continue;
        }


        if (selectTargets && !(SpellSummary[m_creature->m_spells[i]].Targets & (1 << (selectTargets - 1))))
        {
            continue;
        }


        if (selectEffects && !(SpellSummary[m_creature->m_spells[i]].Effects & (1 << (selectEffects - 1))))
        {
            continue;
        }


        if (iMechanic >= 0 && pTempSpell->Mechanic != (uint32)iMechanic)
        {
            continue;
        }


        if (uiPowerCostMin &&  pTempSpell->manaCost < uiPowerCostMin)
        {
            continue;
        }

        if (uiPowerCostMax && pTempSpell->manaCost > uiPowerCostMax)
        {
            continue;
        }


        if (pTempSpell->manaCost > m_creature->GetPower((Powers)pTempSpell->powerType))
        {
            continue;
        }


        pTempRange = GetSpellRangeStore()->LookupEntry(pTempSpell->rangeIndex);


        if (!pTempRange)
        {
            continue;
        }


        if (fRangeMin && pTempRange->maxRange < fRangeMin)
        {
            continue;
        }

        if (fRangeMax && pTempRange->maxRange > fRangeMax)
        {
            continue;
        }


        if (m_creature->IsWithinDistInMap(pTarget, pTempRange->minRange) || !m_creature->IsWithinDistInMap(pTarget, pTempRange->maxRange))
        {
            continue;
        }


        apSpell[uiSpellCount] = pTempSpell;
        ++uiSpellCount;
    }


    if (!uiSpellCount)
    {
        return NULL;
    }

    return apSpell[urand(0, uiSpellCount - 1)];
}
