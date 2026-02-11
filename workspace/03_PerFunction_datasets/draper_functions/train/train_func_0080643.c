P_ArtiTeleportOther(player_t * player)
{
    mobj_t *mo;

    mo = P_SpawnPlayerMissile(player->mo, MT_TELOTHER_FX1);
    if (mo)
    {
        mo->target = player->mo;
    }
}
