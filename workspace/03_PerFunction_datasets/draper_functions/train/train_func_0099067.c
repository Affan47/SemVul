GetExplicitDiscoverySpell(uint32 spellId, Player* player)
{


    SkillDiscoveryMap::const_iterator tab = SkillDiscoveryStore.find(spellId);
    if (tab == SkillDiscoveryStore.end())
        return 0;

    SkillLineAbilityMapBounds bounds = sSpellMgr.GetSkillLineAbilityMapBounds(spellId);
    uint32 skillvalue = bounds.first != bounds.second ? player->GetSkillValue(bounds.first->second->skillId) : 0;

    float full_chance = 0;
    for (SkillDiscoveryList::const_iterator item_iter = tab->second.begin(); item_iter != tab->second.end(); ++item_iter)
        if (item_iter->reqSkillValue <= skillvalue)
            if (!player->HasSpell(item_iter->spellId))
                full_chance += item_iter->chance;

    float rate = full_chance / 100.0f;
    float roll = rand_chance_f() * rate;

    for (SkillDiscoveryList::const_iterator item_iter = tab->second.begin(); item_iter != tab->second.end(); ++item_iter)
    {
        if (item_iter->reqSkillValue > skillvalue)
            continue;

        if (player->HasSpell(item_iter->spellId))
            continue;

        if (item_iter->chance > roll)
            return item_iter->spellId;

        roll -= item_iter->chance;
    }

    return 0;
}
