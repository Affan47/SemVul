send_wm_delete(client_t *c)
{
    int i, n, found = 0;
    Atom *protocols;

    if (XGetWMProtocols(dpy, c->win, &protocols, &n)) {
        for (i=0; i<n; i++) if (protocols[i] == wm_delete) found++;
        XFree(protocols);
    }

    if (found)
        send_xmessage(c->win, wm_protos, wm_delete, NoEventMask);
    else
        XKillClient(dpy, c->win);
}
