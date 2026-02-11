CanTakeMoreActiveSpells(uint32 spellid)
{
    uint8  activecount = 1;
    uint32 chainstartstore[ACTIVE_SPELLS_MAX];

    if (IsPassiveSpell(spellid))
        return true;

    chainstartstore[0] = sSpellMgr.GetFirstSpellInChain(spellid);

    for (PetSpellMap::const_iterator itr = m_spells.begin(); itr != m_spells.end(); ++itr)
    {
        if (itr->second.state == PETSPELL_REMOVED)
            continue;

        if (IsPassiveSpell(itr->first))
            continue;

        uint32 chainstart = sSpellMgr.GetFirstSpellInChain(itr->first);

        uint8 x;

        for (x = 0; x < activecount; ++x)
        {
            if (chainstart == chainstartstore[x])
                break;
        }

        if (x == activecount)
        {
            ++activecount;
            if (activecount > ACTIVE_SPELLS_MAX)
                return false;
            chainstartstore[x] = chainstart;
        }
    }
    return true;
}
