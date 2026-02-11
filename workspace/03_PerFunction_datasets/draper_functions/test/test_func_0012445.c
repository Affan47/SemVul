A_MWandAttack(player_t * player, pspdef_t * psp)
{
    mobj_t *mo;

    mo = P_SpawnPlayerMissile(player->mo, MT_MWAND_MISSILE);
    if (mo)
    {
        mo->thinker.function = P_BlasterMobjThinker;
    }
    S_StartSound(player->mo, SFX_MAGE_WAND_FIRE);
}
