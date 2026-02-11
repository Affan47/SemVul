G_PlayerReborn(int player)
{
    player_t *p;
    int frags[MAXPLAYERS];
    int killcount, itemcount, secretcount;
    unsigned int worldTimer;

    memcpy(frags, players[player].frags, sizeof(frags));
    killcount = players[player].killcount;
    itemcount = players[player].itemcount;
    secretcount = players[player].secretcount;
    worldTimer = players[player].worldTimer;

    p = &players[player];
    memset(p, 0, sizeof(*p));

    memcpy(players[player].frags, frags, sizeof(players[player].frags));
    players[player].killcount = killcount;
    players[player].itemcount = itemcount;
    players[player].secretcount = secretcount;
    players[player].worldTimer = worldTimer;
    players[player].class = PlayerClass[player];

    p->usedown = p->attackdown = true;
    p->playerstate = PST_LIVE;
    p->health = MAXHEALTH;
    p->readyweapon = p->pendingweapon = WP_FIRST;
    p->weaponowned[WP_FIRST] = true;
    p->messageTics = 0;
    p->lookdir = 0;
    localQuakeHappening[player] = false;
    if (p == &players[consoleplayer])
    {
        SB_state = -1;
        inv_ptr = 0;
        curpos = 0;
        viewangleoffset = 0;
    }
}
