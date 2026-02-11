send_connect(atransport *t)
{
    D("Calling send_connect \n");
    apacket *cp = get_apacket();
    cp->msg.command = A_CNXN;
    cp->msg.arg0 = A_VERSION;
    cp->msg.arg1 = MAX_PAYLOAD;
    cp->msg.data_length = fill_connect_data((char *)cp->data,
                                            sizeof(cp->data));
    send_packet(cp, t);
}
