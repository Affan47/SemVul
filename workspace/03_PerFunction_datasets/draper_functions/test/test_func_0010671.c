ah_state_waiting(panel *p)
{
    ENTER;
    if (p->ah_state != ah_state_waiting) {
        p->ah_state = ah_state_waiting;
        hpid = g_timeout_add(2 * PERIOD, (GSourceFunc) ah_state_hidden, p);
    } else if (!p->ah_far) {
        g_source_remove(hpid);
        hpid = 0;
        ah_state_visible(p);
    }
    RET(FALSE);
}
