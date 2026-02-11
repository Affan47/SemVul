bkn_cmd_thread(void *context)
{
    bkn_thread_ctrl_t *tc = (bkn_thread_ctrl_t *)context;
    kcom_msg_t kmsg;
    unsigned int len, rlen;

    bkn_thread_boot(tc);

    DBG_VERB(("Command thread starting\n"));
    tc->state = 1;
    while (!bkn_thread_should_stop(tc)) {
        len = sizeof(kmsg);
        tc->state = 2;
        if (PROXY_RECV(KCOM_CHAN_KNET, &kmsg, &len) >= 0) {
            DBG_VERB(("Received %d bytes from KCOM_CHAN_CMD\n", len));
            tc->state = 3;
            rlen = bkn_handle_cmd_req(&kmsg, len);
            tc->state = 4;
            if (rlen > 0) {
                PROXY_SEND(KCOM_CHAN_KNET, &kmsg, rlen);
            }
        } else {

            bkn_sleep(1);
        }
    }
    DBG_VERB(("Command thread done\n"));

    bkn_thread_exit(tc);
    return 0;
}
