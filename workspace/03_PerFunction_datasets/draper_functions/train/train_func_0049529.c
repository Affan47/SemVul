jdwp_tracker_ready( asocket*  s )
{
    JdwpTracker*  t = (JdwpTracker*) s;

    if (t->need_update) {
        apacket*  p = get_apacket();
        t->need_update = 0;
        p->len = jdwp_process_list_msg((char*)p->data, sizeof(p->data));
        s->peer->enqueue(s->peer, p);
    }
}
