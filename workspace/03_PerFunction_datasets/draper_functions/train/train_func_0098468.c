NET_CL_Connect(net_addr_t *addr, net_connect_data_t *data)
{
    int start_time;
    int last_send_time;

    server_addr = addr;

    memcpy(net_local_wad_sha1sum, data->wad_sha1sum, sizeof(sha1_digest_t));
    memcpy(net_local_deh_sha1sum, data->deh_sha1sum, sizeof(sha1_digest_t));
    net_local_is_freedoom = data->is_freedoom;


    client_context = NET_NewContext();


    if (!addr->module->InitClient())
    {
        return false;
    }

    NET_AddModule(client_context, addr->module);

    net_client_connected = true;
    net_client_received_wait_data = false;


    NET_Conn_InitClient(&client_connection, addr);


    start_time = I_GetTimeMS();
    last_send_time = -1;

    while (client_connection.state == NET_CONN_STATE_CONNECTING)
    {
        int nowtime = I_GetTimeMS();


        if (nowtime - last_send_time > 1000 || last_send_time < 0)
        {
            NET_CL_SendSYN(data);
            last_send_time = nowtime;
        }


        if (nowtime - start_time > 5000)
        {
            break;
        }


        NET_CL_Run();


        NET_SV_Run();


        I_Sleep(1);
    }

    if (client_connection.state == NET_CONN_STATE_CONNECTED)
    {


        client_state = CLIENT_STATE_WAITING_LAUNCH;
        drone = data->drone;

        return true;
    }
    else
    {


        NET_CL_Shutdown();

        return false;
    }
}
