output_thread(void *_t)
{
    atransport *t = _t;
    apacket *p;

    D("%s: starting transport output thread on fd %d, SYNC online (%d)\n",
       t->serial, t->fd, t->sync_token + 1);
    p = get_apacket();
    p->msg.command = A_SYNC;
    p->msg.arg0 = 1;
    p->msg.arg1 = ++(t->sync_token);
    p->msg.magic = A_SYNC ^ 0xffffffff;
    if(write_packet(t->fd, t->serial, &p)) {
        put_apacket(p);
        D("%s: failed to write SYNC packet\n", t->serial);
        goto oops;
    }

    D("%s: data pump started\n", t->serial);
    for(;;) {
        p = get_apacket();

        if(t->read_from_remote(p, t) == 0){
            D("%s: received remote packet, sending to transport\n",
              t->serial);
            if(write_packet(t->fd, t->serial, &p)){
                put_apacket(p);
                D("%s: failed to write apacket to transport\n", t->serial);
                goto oops;
            }
        } else {
            D("%s: remote read failed for transport\n", t->serial);
            put_apacket(p);
            break;
        }
    }

    D("%s: SYNC offline for transport\n", t->serial);
    p = get_apacket();
    p->msg.command = A_SYNC;
    p->msg.arg0 = 0;
    p->msg.arg1 = 0;
    p->msg.magic = A_SYNC ^ 0xffffffff;
    if(write_packet(t->fd, t->serial, &p)) {
        put_apacket(p);
        D("%s: failed to write SYNC apacket to transport", t->serial);
    }

oops:
    D("%s: transport output thread is exiting\n", t->serial);
    kick_transport(t);
    transport_unref(t);
    return 0;
}
