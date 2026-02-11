GetProfessionSpellMinLevel(uint32 spellId)
{
    uint32 s2l[8][3] =
    {

         { 0,   5,  5 },
         { 0,   5,  5 },
         { 0,  10, 10 },
         { 10, 20, 10 },
         { 25, 35, 10 },
         { 40, 50, 10 },
         { 55, 65, 10 },
         { 75, 75, 10 },
    };

    uint32 rank = GetSpellRank(spellId);
    if (rank >= 8)
        return 0;

    SkillLineAbilityMapBounds bounds = GetSkillLineAbilityMapBounds(spellId);
    if (bounds.first == bounds.second)
        return 0;

    switch (bounds.first->second->skillId)
    {
        case SKILL_FISHING:
            return s2l[rank][2];
        case SKILL_HERBALISM:
        case SKILL_MINING:
        case SKILL_SKINNING:
            return s2l[rank][0];
        default:
            return s2l[rank][1];
    }
}
