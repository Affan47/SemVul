client_player_get(int num) {
    if (num < 0 || num >= MAXPLAYERS)
        return NULL;
    const client_player_t *player = &players[num];
    if (!PLAYER_USED(player))
        return NULL;
    return player;
}
