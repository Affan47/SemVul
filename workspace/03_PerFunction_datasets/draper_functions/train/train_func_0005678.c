slot_save( int id, char *name )
{
    FILE *file = 0;
    char path[512];
    int i, j;


    COMPILE_TIME_ASSERT(StoreHighestSupportedVersion <= StoreVersionLimit);

    sprintf( path, "%s/lg_save_%i", config.dir_name, id );

    if ( ( file = fopen( path, "w" ) ) == 0 ) {
        fprintf( stderr, tr("%s: not found\n"), path );
        return 0;
    }

    strcpy( slots[id].name, name );

    slot_write_name( &slots[id], file );

    save_int(file, StoreHighestSupportedVersion);

    save_int( file, camp_loaded );
    if ( camp_loaded ) {
        save_string( file, camp_fname );
        save_string( file, camp_cur_scen->id );
    }

    save_string( file, scen_info->fname );
    save_int( file, config.fog_of_war );
    save_int( file, config.supply );
    save_int( file, config.weather );
    save_int( file, config.deploy_turn );
    save_int( file, config.purchase );
    save_int( file, turn );
    save_int( file, player_get_index( cur_player ) );

    list_reset( players );
    for ( i = 0; i < players->count; i++ )
        save_player( file, list_next( players ) );

    list_reset( units );
    save_int( file, units->count );
    for ( i = 0; i < units->count; i++ )
        save_unit( file, list_next( units ) );

    list_reset( reinf );
    save_int( file, reinf->count );
    for ( i = 0; i < reinf->count; i++ )
        save_unit( file, list_next( reinf ) );
    list_reset( avail_units );
    save_int( file, avail_units->count );
    for ( i = 0; i < avail_units->count; i++ )
        save_unit( file, list_next( avail_units ) );

    save_int( file, map_w );
    save_int( file, map_h );
    for ( i = 0; i < map_w; i++ )
        for ( j = 0; j < map_h; j++ )
            save_map_tile_units( file, map_tile( i, j ) );
    for ( i = 0; i < map_w; i++ )
        for ( j = 0; j < map_h; j++ )
            save_map_tile_flag( file, map_tile( i, j ) );
    fclose( file );

    slots[id].valid = 1;
    return 1;
}
