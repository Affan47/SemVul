NET_SV_ParseSYN(net_packet_t *packet,
                            net_client_t *client,
                            net_addr_t *addr)
{
    unsigned int magic;
    net_connect_data_t data;
    char *player_name;
    char *client_version;
    int i;


    if (!NET_ReadInt32(packet, &magic))
    {
        return;
    }

    if (magic != NET_MAGIC_NUMBER)
    {


        return;
    }


    client_version = NET_ReadString(packet);

    if (client_version == NULL)
    {
        return;
    }

    if (strcmp(client_version, PACKAGE_STRING) != 0)
    {


        if (M_CheckParm("-ignoreversion") == 0)
        {
            NET_SV_SendReject(addr,
                "Different " PACKAGE_NAME " versions cannot play a net game!\n"
                "Version mismatch: server version is: " PACKAGE_STRING);
            return;
        }
    }


    if (!NET_ReadConnectData(packet, &data))
    {
        return;
    }

    if (!D_ValidGameMode(data.gamemission, data.gamemode))
    {
        return;
    }


    if (data.max_players > NET_MAXPLAYERS)
    {
        return;
    }


    player_name = NET_ReadString(packet);

    if (player_name == NULL)
    {
        return;
    }


    if (server_state != SERVER_WAITING_LAUNCH)
    {
        NET_SV_SendReject(addr, "Server is not currently accepting connections");
        return;
    }


    if (client == NULL)
    {


        for (i=0; i<MAXNETNODES; ++i)
        {
            if (!clients[i].active)
            {
                client = &clients[i];
                break;
            }
        }

        if (client == NULL)
        {
            return;
        }
    }
    else
    {


        if (client->connection.state == NET_CONN_STATE_DISCONNECTED)
        {
            client->active = false;
        }
    }


    if (!client->active)
    {
        int num_players;


        NET_SV_AssignPlayers();
        num_players = NET_SV_NumPlayers();

        if ((!data.drone && num_players >= NET_SV_MaxPlayers())
         || NET_SV_NumClients() >= MAXNETNODES)
        {
            NET_SV_SendReject(addr, "Server is full!");
            return;
        }


        if (num_players == 0 && !data.drone)
        {
            sv_gamemode = data.gamemode;
            sv_gamemission = data.gamemission;
        }


        memcpy(client->wad_sha1sum, data.wad_sha1sum, sizeof(sha1_digest_t));
        memcpy(client->deh_sha1sum, data.deh_sha1sum, sizeof(sha1_digest_t));
        client->is_freedoom = data.is_freedoom;
        client->max_players = data.max_players;


        if (data.gamemode != sv_gamemode || data.gamemission != sv_gamemission)
        {
            NET_SV_SendReject(addr, "You are playing the wrong game!");
            return;
        }


        NET_SV_InitNewClient(client, addr, player_name);

        client->recording_lowres = data.lowres_turn;
        client->drone = data.drone;
        client->player_class = data.player_class;
    }

    if (client->connection.state == NET_CONN_STATE_WAITING_ACK)
    {

        client->connection.last_send_time = -1;
    }
}
