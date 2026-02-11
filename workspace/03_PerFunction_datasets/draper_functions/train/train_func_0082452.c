player_get_by_nation( Nation *nation )
{
    int i;
    Player *player;
    list_reset( players );
    while ( ( player = list_next( players ) ) ) {
        for ( i = 0; i < player->nation_count; i++ )
            if ( nation == player->nations[i] )
                return player;
    }
    return 0;
}
