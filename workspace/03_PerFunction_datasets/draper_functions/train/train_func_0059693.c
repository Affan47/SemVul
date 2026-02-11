NET_SV_ParseGameStart(net_packet_t *packet, net_client_t *client)
{
    net_gamesettings_t settings;


    if (server_state != SERVER_WAITING_START)
    {
        return;
    }

    if (client == NET_SV_Controller())
    {
        if (!NET_ReadSettings(packet, &settings))
        {


            return;
        }


        if (!NET_ValidGameSettings(sv_gamemode, sv_gamemission, &settings))
        {
            return;
        }

        sv_settings = settings;
    }

    client->ready = true;

    CheckStartGame();


    SendAllWaitingData();
}
