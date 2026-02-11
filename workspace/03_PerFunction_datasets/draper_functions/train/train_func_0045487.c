P_MonsterFallingDamage(mobj_t * mo)
{
    int damage;
    int mom;

    mom = abs(mo->momz);
    if (mom > 35 * FRACUNIT)
    {
        damage = 10000;
    }
    else
    {
        damage = ((mom - (23 * FRACUNIT)) * 6) >> FRACBITS;
    }
    damage = 10000;
    P_DamageMobj(mo, NULL, NULL, damage);
}
