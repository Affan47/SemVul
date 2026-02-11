load_config( )
{
    char file_name[512];
    PData *pd;

    check_config_dir_name();
    reset_config();

    sprintf( file_name, "%s/%s", config.dir_name, "lgeneral.conf" );
    if ( ( pd = parser_read_file( "config", file_name ) ) == 0 ) {
        fprintf( stderr, "%s\n", parser_get_error() );
        return;
    }

    parser_get_int( pd, "grid", &config.grid );
    parser_get_int( pd, "tran", &config.tran );
    parser_get_int( pd, "bar", &config.show_bar );
    parser_get_int( pd, "width", &config.width );
    parser_get_int( pd, "height", &config.height );
    parser_get_int( pd, "fullscreen", &config.fullscreen );
    parser_get_int( pd, "anim_speed", &config.anim_speed );
    parser_get_int( pd, "supply", &config.supply );
    parser_get_int( pd, "weather", &config.weather );
    parser_get_int( pd, "fog_of_war", &config.fog_of_war );
    parser_get_int( pd, "cpu_turn", &config.show_cpu_turn );
    parser_get_int( pd, "deploy", &config.deploy_turn );
    parser_get_int( pd, "purchase", &config.purchase );
    parser_get_int( pd, "ai_debug", &config.ai_debug );
    parser_get_int( pd, "sound_on", &config.sound_on );
    parser_get_int( pd, "sound_volume", &config.sound_volume );
    parser_get_int( pd, "music_on", &config.music_on );
    parser_get_int( pd, "music_volume", &config.music_volume );
    parser_free( &pd );
}
