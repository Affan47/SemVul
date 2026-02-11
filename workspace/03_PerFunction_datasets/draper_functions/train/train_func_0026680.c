NET_CL_ParseResendRequest(net_packet_t *packet)
{
    static unsigned int start;
    static unsigned int end;
    static unsigned int num_tics;

    if (drone)
    {


        return;
    }

    if (!NET_ReadInt32(packet, &start)
     || !NET_ReadInt8(packet, &num_tics))
    {
        return;
    }

    end = start + num_tics - 1;


    while (start <= end
        && (!send_queue[start % BACKUPTICS].active
         || send_queue[start % BACKUPTICS].seq != start))
    {
        ++start;
    }

    while (start <= end
        && (!send_queue[end % BACKUPTICS].active
         || send_queue[end % BACKUPTICS].seq != end))
    {
        --end;
    }


    if (start <= end)
    {


        NET_CL_SendTics(start, end);
    }
}
