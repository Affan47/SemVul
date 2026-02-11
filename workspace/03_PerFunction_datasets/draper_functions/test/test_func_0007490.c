P_SpawnPlayer(mapthing_t* mthing)
{
    player_t*   p;
    fixed_t     x;
    fixed_t     y;
    fixed_t     z;
    mobj_t*     mobj;

    if(mthing->type == 0)
        return;


    if(!playeringame[mthing->type-1])
        return;

    p = &players[mthing->type-1];

    if (p->playerstate == PST_REBORN)
        G_PlayerReborn (mthing->type-1);

    x       = mthing->x << FRACBITS;
    y       = mthing->y << FRACBITS;
    z       = ONFLOORZ;
    mobj    = P_SpawnMobj (x,y,z, MT_PLAYER);


    if(mthing->type > 1)
        mobj->flags |= (mthing->type-1)<<MF_TRANSSHIFT;

    mobj->angle  = ANG45 * (mthing->angle/45);
    mobj->player = p;
    mobj->health = p->health;

    p->mo               = mobj;
    p->playerstate      = PST_LIVE;
    p->refire           = 0;
    p->message          = NULL;
    p->damagecount      = 0;
    p->bonuscount       = 0;
    p->extralight       = 0;
    p->fixedcolormap    = 0;
    p->viewheight       = VIEWHEIGHT;


    P_SetupPsprites(p);


    stonecold = false;


    if(gamemap == 10)
        p->weaponowned[wp_sigil] = true;


    if(deathmatch)
    {
        int i;

        p->accuracy = 50;
        p->questflags = QF_ALLQUESTS;

        for(i = 0; i < NUMCARDS; i++)
            p->cards[i] = true;
    }


    if(workparm)
        p->cheats |= CF_GODMODE;

    if(mthing->type - 1 == consoleplayer)
    {

        ST_Start ();

        HU_Start ();
    }
}
