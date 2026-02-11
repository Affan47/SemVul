NET_Query_MasterResponse(net_packet_t *packet)
{
    unsigned int packet_type;
    unsigned int result;

    if (!NET_ReadInt16(packet, &packet_type)
     || !NET_ReadInt16(packet, &result))
    {
        return;
    }

    if (packet_type == NET_MASTER_PACKET_TYPE_ADD_RESPONSE)
    {
        if (result != 0)
        {


            if (!registered_with_master)
            {
                printf("Registered with master server at %s\n",
                       MASTER_SERVER_ADDRESS);
                registered_with_master = true;
            }
        }
        else
        {


            printf("Failed to register with master server at %s\n",
                   MASTER_SERVER_ADDRESS);
        }

        got_master_response = true;
    }
}
