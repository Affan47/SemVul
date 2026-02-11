InitConnectData(net_connect_data_t *connect_data)
{
    int i;


    connect_data->gamemode = gamemode;
    connect_data->gamemission = hexen;

    connect_data->lowres_turn = false;
    connect_data->drone = false;
    connect_data->max_players = MAXPLAYERS;


    i = M_CheckParmWithArgs("-class", 1);

    if (i > 0)
    {
        connect_data->player_class = atoi(myargv[i + 1]);
    }
    else
    {
        connect_data->player_class = PCLASS_FIGHTER;
    }


    W_Checksum(connect_data->wad_sha1sum);
    memset(connect_data->deh_sha1sum, 0, sizeof(sha1_digest_t));

    connect_data->is_freedoom = 0;
}
