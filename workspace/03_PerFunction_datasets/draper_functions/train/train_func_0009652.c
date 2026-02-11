player_think() {
    int playerno;
    player_t *player = &players[0];
    for (playerno = 0; playerno < MAXPLAYERS; playerno++, player++) {
        if (!PLAYER_USED(player))
            continue;


        lua_pushliteral(player->L, "player_think");
        lua_rawget(player->L, LUA_GLOBALSINDEX);
        lua_pushliteral(player->L, "events");
        lua_rawget(player->L, LUA_REGISTRYINDEX);
        player->output_client = player->bot_output_client;
        player_call_user_lua("during botcode execution", player, 1);
        player->output_client = NULL;


        player_init_events(player);
    }
}
