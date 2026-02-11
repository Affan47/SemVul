GetSkillDiscoverySpell(uint32 skillId, uint32 spellId, Player* player)
{
    uint32 skillvalue = skillId ? player->GetSkillValue(skillId) : 0;


    SkillDiscoveryMap::const_iterator tab = SkillDiscoveryStore.find(spellId);

    if (tab != SkillDiscoveryStore.end())
    {
        for (SkillDiscoveryList::const_iterator item_iter = tab->second.begin(); item_iter != tab->second.end(); ++item_iter)
        {
            if (roll_chance_f(item_iter->chance * sWorld.getConfig(CONFIG_FLOAT_RATE_SKILL_DISCOVERY)) &&
                    item_iter->reqSkillValue <= skillvalue &&
                    !player->HasSpell(item_iter->spellId))
                return item_iter->spellId;
        }

        return 0;
    }

    if (!skillId)
        return 0;


    tab = SkillDiscoveryStore.find(-(int32)skillId);
    if (tab != SkillDiscoveryStore.end())
    {
        for (SkillDiscoveryList::const_iterator item_iter = tab->second.begin(); item_iter != tab->second.end(); ++item_iter)
        {
            if (roll_chance_f(item_iter->chance * sWorld.getConfig(CONFIG_FLOAT_RATE_SKILL_DISCOVERY)) &&
                    item_iter->reqSkillValue <= skillvalue &&
                    !player->HasSpell(item_iter->spellId))
                return item_iter->spellId;
        }

        return 0;
    }

    return 0;
}
