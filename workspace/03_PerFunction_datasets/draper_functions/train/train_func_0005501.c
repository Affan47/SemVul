engine_human_player(int *human_count)
{
    Player *human = 0;
    int count = 0;
    int i;
    for ( i = 0; i < players->count; i++ ) {
        Player *player = list_get( players, i );
        if ( player->ctrl == PLAYER_CTRL_HUMAN ) {
            if ( count == 0 )
                human = player;
            count++;
        }
    }
    if (human_count) *human_count = count;
    return human;
}
