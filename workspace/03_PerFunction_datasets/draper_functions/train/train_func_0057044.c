weapon_hit_bonus(struct obj *weapon)
{
    int type, wep_type, skill, bonus = 0;
    static const char bad_skill[] = "weapon_hit_bonus: bad skill %d";

    wep_type = weapon_type(weapon);

    type = (u.twoweap && (weapon == uwep || weapon == uswapwep)) ?
        P_TWO_WEAPON_COMBAT : wep_type;
    if (type == P_NONE)
    {
        bonus = 0;
    } else if (type <= P_LAST_WEAPON)
    {
        switch (P_SKILL(type))
        {
        default: impossible(bad_skill, P_SKILL(type));
        case P_ISRESTRICTED:
        case P_UNSKILLED:   bonus = -4; break;
        case P_BASIC:       bonus =  0; break;
        case P_SKILLED:     bonus =  2; break;
        case P_EXPERT:      bonus =  3; break;
        }
    } else if (type == P_TWO_WEAPON_COMBAT)
    {
        skill = P_SKILL(P_TWO_WEAPON_COMBAT);
        if (P_SKILL(wep_type) < skill) skill = P_SKILL(wep_type);
        switch (skill)
        {
        default: impossible(bad_skill, skill);
        case P_ISRESTRICTED:
        case P_UNSKILLED:   bonus = -9; break;
        case P_BASIC:	bonus = -7; break;
        case P_SKILLED:	bonus = -5; break;
        case P_EXPERT:	bonus = -3; break;
        }
    } else if (type == P_BARE_HANDED_COMBAT)
    {


        bonus = P_SKILL(type);
        bonus = max(bonus,P_UNSKILLED) - 1;
        bonus = ((bonus + 2) * (martial_bonus() ? 2 : 1)) / 2;
    }


    if (u.usteed)
    {
        switch (P_SKILL(P_RIDING))
        {
        case P_ISRESTRICTED:
        case P_UNSKILLED:   bonus -= 2; break;
        case P_BASIC:       bonus -= 1; break;
        case P_SKILLED:     break;
        case P_EXPERT:      break;
        }
        if (u.twoweap) bonus -= 2;
    }

    return bonus;
}
