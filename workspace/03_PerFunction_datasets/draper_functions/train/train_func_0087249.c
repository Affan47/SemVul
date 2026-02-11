A_Punch(player_t* player, pspdef_t* psp)
{
    angle_t     angle;
    int         damage;
    int         slope;
    int         sound;
    int         stamina;
    int         t;


    stamina = player->stamina;
    damage = (P_Random() & ((stamina/10) + 7)) * ((stamina/10) + 2);

    if(player->powers[pw_strength])
        damage *= 10;

    angle = player->mo->angle;
    t = P_Random();
    angle += (t - P_Random()) << 18;
    slope = P_AimLineAttack (player->mo, angle, PLAYERMELEERANGE);
    P_LineAttack (player->mo, angle, PLAYERMELEERANGE, slope, damage);


    if(linetarget)
    {

        if(linetarget->flags & MF_NOBLOOD)
            sound = sfx_mtalht;
        else
            sound = sfx_meatht;

        S_StartSound (player->mo, sound);
        player->mo->angle = R_PointToAngle2 (player->mo->x,
                                             player->mo->y,
                                             linetarget->x,
                                             linetarget->y);


        player->mo->flags |= MF_JUSTATTACKED;


        P_DoPunchAlert(player->mo, linetarget);
    }
    else
        S_StartSound (player->mo, sfx_swish);
}
