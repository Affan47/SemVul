player_is_ally( Player *player, Player *second )
{
    Player *ally;
    if ( player == second || player == 0 ) return 1;
    list_reset( player->allies );
    while ( ( ally = list_next( player->allies ) ) )
        if ( ally == second )
            return 1;
    return 0;
}
