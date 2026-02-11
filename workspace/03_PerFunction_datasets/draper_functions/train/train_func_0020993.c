joust(struct monst *mon, struct obj *obj)
{
    int skill_rating, joust_dieroll;

    if (Fumbling || Stunned) return 0;

    if (obj != uwep && (obj != uswapwep || !u.twoweap)) return 0;


    skill_rating = P_SKILL(weapon_type(obj));
    if (u.twoweap && P_SKILL(P_TWO_WEAPON_COMBAT) < skill_rating)
            skill_rating = P_SKILL(P_TWO_WEAPON_COMBAT);
    if (skill_rating == P_ISRESTRICTED) skill_rating = P_UNSKILLED;


    if ((joust_dieroll = rn2(5)) < skill_rating)
    {
        if (joust_dieroll == 0 && rnl(50) == (50-1) &&
            !unsolid(mon->data) && !obj_resists(obj, 0, 100))
                return -1;
        return 1;
    }
    return 0;
}
