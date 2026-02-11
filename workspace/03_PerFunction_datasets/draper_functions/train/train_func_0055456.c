NET_SV_PumpSendQueue(net_client_t *client)
{
    net_full_ticcmd_t cmd;
    int recv_index;
    int num_players;
    int i;
    int starttic, endtic;


    if (client->sendseq - NET_SV_LatestAcknowledged() > 40)
    {
        return;
    }


    recv_index = client->sendseq - recvwindow_start;

    if (recv_index < 0 || recv_index >= BACKUPTICS)
    {
        return;
    }


    num_players = 0;

    for (i=0; i<NET_MAXPLAYERS; ++i)
    {
        if (sv_players[i] == client)
        {


            continue;
        }

        if (sv_players[i] == NULL || !ClientConnected(sv_players[i]))
        {
            continue;
        }

        if (!recvwindow[recv_index][i].active)
        {


            return;
        }

        ++num_players;
    }


    if (num_players == 0 && client->sendseq > recvwindow_start + 10)
    {
        return;
    }


    cmd.seq = client->sendseq;


    cmd.latency = 0;

    for (i=0; i<NET_MAXPLAYERS; ++i)
    {
        net_client_recv_t *recvobj;

        if (sv_players[i] == client)
        {


            cmd.playeringame[i] = false;
            continue;
        }

        if (sv_players[i] == NULL || !recvwindow[recv_index][i].active)
        {
            cmd.playeringame[i] = false;
            continue;
        }

        cmd.playeringame[i] = true;

        recvobj = &recvwindow[recv_index][i];

        cmd.cmds[i] = recvobj->diff;

        if (recvobj->latency > cmd.latency)
            cmd.latency = recvobj->latency;
    }


    client->sendqueue[client->sendseq % BACKUPTICS] = cmd;


    starttic = client->sendseq - sv_settings.extratics;
    endtic = client->sendseq;

    if (starttic < 0)
        starttic = 0;

    NET_SV_SendTics(client, starttic, endtic);

    ++client->sendseq;
}
