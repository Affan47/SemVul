P_CalcHeight (player_t* player)
{
    int     angle;
    fixed_t bob;


    player->bob =
        FixedMul (player->mo->momx, player->mo->momx)
        + FixedMul (player->mo->momy,player->mo->momy);

    player->bob >>= 2;

    if (player->bob>MAXBOB)
        player->bob = MAXBOB;


    if (!onground)
    {


        player->viewz = player->mo->z + player->viewheight;
        return;
    }

    angle = (FINEANGLES/20*leveltime)&FINEMASK;
    bob = FixedMul ( player->bob/2, finesine[angle]);


    if (player->playerstate == PST_LIVE)
    {
        player->viewheight += player->deltaviewheight;

        if (player->viewheight > VIEWHEIGHT)
        {
            player->viewheight = VIEWHEIGHT;
            player->deltaviewheight = 0;
        }

        if (player->viewheight < VIEWHEIGHT/2)
        {
            player->viewheight = VIEWHEIGHT/2;
            if (player->deltaviewheight <= 0)
                player->deltaviewheight = 1;
        }

        if (player->deltaviewheight)
        {
            player->deltaviewheight += FRACUNIT/4;
            if (!player->deltaviewheight)
                player->deltaviewheight = 1;
        }
    }
    player->viewz = player->mo->z + player->viewheight + bob;


    if(player->mo->flags & MF_FEETCLIPPED)
        player->viewz -= 13*FRACUNIT;

    if (player->viewz > player->mo->ceilingz-4*FRACUNIT)
        player->viewz = player->mo->ceilingz-4*FRACUNIT;


    if (player->viewz < player->mo->floorz)
        player->viewz = player->mo->floorz;
}
