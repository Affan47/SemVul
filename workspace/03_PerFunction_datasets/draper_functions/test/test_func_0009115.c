A_CFlameAttack(player_t * player, pspdef_t * psp)
{
    mobj_t *mo;

    mo = P_SpawnPlayerMissile(player->mo, MT_CFLAME_MISSILE);
    if (mo)
    {
        mo->thinker.function = P_BlasterMobjThinker;
        mo->special1.i = 2;
    }

    player->mana[MANA_2] -= WeaponManaUse[player->class][player->readyweapon];
    S_StartSound(player->mo, SFX_CLERIC_FLAME_FIRE);
}
