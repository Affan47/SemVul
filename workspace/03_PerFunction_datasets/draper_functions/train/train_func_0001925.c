IsSkillBonusSpell(uint32 spellId) const
{
    SkillLineAbilityMapBounds bounds = GetSkillLineAbilityMapBounds(spellId);

    for (SkillLineAbilityMap::const_iterator _spell_idx = bounds.first; _spell_idx != bounds.second; ++_spell_idx)
    {
        SkillLineAbilityEntry const* pAbility = _spell_idx->second;
        if (!pAbility || pAbility->learnOnGetSkill != ABILITY_LEARNED_ON_GET_PROFESSION_SKILL)
            continue;

        if (pAbility->req_skill_value > 0)
            return true;
    }

    return false;
}
