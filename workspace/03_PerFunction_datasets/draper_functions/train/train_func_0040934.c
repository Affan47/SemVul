A_LightningReady(player_t * player, pspdef_t * psp)
{
    A_WeaponReady(player, psp);
    if (P_Random() < 160)
    {
        S_StartSound(player->mo, SFX_MAGE_LIGHTNING_READY);
    }
}
