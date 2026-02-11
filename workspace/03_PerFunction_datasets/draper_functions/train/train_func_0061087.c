P_PlayerInSpecialSector (player_t* player)
{
    sector_t*	sector;

    sector = player->mo->subsector->sector;


    if (player->mo->z != sector->floorheight)
        return;


    switch (sector->special)
    {
    case 5:


        if(!player->powers[pw_ironfeet])
            player->nukagecount += 2;
        break;

    case 16:

        if(!player->powers[pw_ironfeet])
            player->nukagecount += 4;
        break;

    case 4:
    case 7:

        if(!player->powers[pw_ironfeet])
            if(!(leveltime & 0x1f))
                P_DamageMobj(player->mo, NULL, NULL, 5);
        break;

    case 9:


        sector->special = 0;
        if(player - players == consoleplayer)
            S_StartSound(NULL, sfx_yeah);
        break;

    case 11:

        player->cheats &= ~CF_GODMODE;

        if (!(leveltime&0x1f))
            P_DamageMobj (player->mo, NULL, NULL, 20);

        if (player->health <= 10)
            G_ExitLevel(0);
        break;

    case 15:

        P_DamageMobj(player->mo, NULL, NULL, 999);
        break;


    case 18:

        {
            int tagval = sector->tag - 100;
            fixed_t force;
            angle_t angle;

            if(player->cheats & CF_NOCLIP)
                return;

            force = (tagval % 10) << 12;
            angle = (tagval / 10) << 29;

            P_Thrust(player, angle, force);
        }
        break;

    default:
        I_Error ("P_PlayerInSpecialSector: "
                 "unknown special %i",
                 sector->special);
        break;
    };
}
