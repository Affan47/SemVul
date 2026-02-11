A_CStaffCheck(player_t * player, pspdef_t * psp)
{
    mobj_t *pmo;
    int damage;
    int newLife;
    angle_t angle;
    int slope;
    int i;

    pmo = player->mo;
    damage = 20 + (P_Random() & 15);
    PuffType = MT_CSTAFFPUFF;
    for (i = 0; i < 3; i++)
    {
        angle = pmo->angle + i * (ANG45 / 16);
        slope = P_AimLineAttack(pmo, angle, 1.5 * MELEERANGE);
        if (linetarget)
        {
            P_LineAttack(pmo, angle, 1.5 * MELEERANGE, slope, damage);
            pmo->angle = R_PointToAngle2(pmo->x, pmo->y,
                                         linetarget->x, linetarget->y);
            if ((linetarget->player || linetarget->flags & MF_COUNTKILL)
                && (!(linetarget->flags2 & (MF2_DORMANT + MF2_INVULNERABLE))))
            {
                newLife = player->health + (damage >> 3);
                newLife = newLife > 100 ? 100 : newLife;
                pmo->health = player->health = newLife;
                P_SetPsprite(player, ps_weapon, S_CSTAFFATK2_1);
            }
            player->mana[MANA_1] -=
                WeaponManaUse[player->class][player->readyweapon];
            break;
        }
        angle = pmo->angle - i * (ANG45 / 16);
        slope = P_AimLineAttack(player->mo, angle, 1.5 * MELEERANGE);
        if (linetarget)
        {
            P_LineAttack(pmo, angle, 1.5 * MELEERANGE, slope, damage);
            pmo->angle = R_PointToAngle2(pmo->x, pmo->y,
                                         linetarget->x, linetarget->y);
            if (linetarget->player || linetarget->flags & MF_COUNTKILL)
            {
                newLife = player->health + (damage >> 4);
                newLife = newLife > 100 ? 100 : newLife;
                pmo->health = player->health = newLife;
                P_SetPsprite(player, ps_weapon, S_CSTAFFATK2_1);
            }
            player->mana[MANA_1] -=
                WeaponManaUse[player->class][player->readyweapon];
            break;
        }
    }
}
