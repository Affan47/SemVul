cimd_open_connection(SMSCenter *smsc)
{

    char *tmpbuff = NULL;
    int ret = 0;

    int cmd = 0, err = 0;


    tmpbuff = gw_malloc(10 * 1024);
    memset(tmpbuff, 0, 10*1024);


    smsc->socket = tcpip_connect_to_server(smsc->cimd_hostname, smsc->cimd_port,
	NULL);


    if (smsc->socket == -1)
        goto error;


    for (;;) {
        ret = smscenter_read_into_buffer(smsc);
        if (strstr(smsc->buffer, "CIMD rel 1.37\n") != NULL)
            break;
        if (ret < 0) goto logout;
    }

    debug("bb.sms.cimd", 0, "got the server identification tag");

    smscenter_remove_from_buffer(smsc, smsc->buflen);


    sprintf(tmpbuff, "%c%s%c%s%c%s%c%s%c%c",
            0x02,
            "01", 0x09,
            smsc->cimd_username, 0x09,
            smsc->cimd_password, 0x09,
            "11",
            0x03, 0x0A);

    ret = write_to_socket(smsc->socket, tmpbuff);
    if (ret < 0) goto logout;


    smsc->cimd_last_spoke = 0;

    if (expect_acknowledge(smsc, &cmd, &err) < 1)
        goto logout;

    debug("bb.sms.cimd", 0, "logged in");

    gw_free(tmpbuff);
    return 0;

logout:
    cimd_close(smsc);

error:
    error(0, "cimd_open: could not open/handshake");
    gw_free(tmpbuff);
    return -1;
}
