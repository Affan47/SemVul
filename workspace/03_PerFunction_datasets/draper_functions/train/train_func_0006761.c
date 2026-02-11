Gcwbutaction (Widget w, XEvent *evp, char **app, unsigned int *anp) {
    Gwidget_t *widget;
    Gevent_t gev;
    PIXpoint_t pp;
    int wi, xtype, bn;

    widget = findwidget ((unsigned long) w, G_CANVASWIDGET);
    switch ((xtype = evp->type)) {
    case ButtonPress:
    case ButtonRelease:
        gev.type = G_MOUSE;
        gev.code = (xtype == ButtonPress) ? G_DOWN : G_UP;
        gev.data = evp->xbutton.button - Button1;
        if (gev.data > 4)
            return;
        pp.x = evp->xbutton.x, pp.y = evp->xbutton.y;
        gev.p = Gppixtodraw (widget, pp);
        bn = WCU->bstate[gev.data];
        WCU->bstate[gev.data] = (xtype == ButtonPress) ? 1 : 0;
        bn = WCU->bstate[gev.data] - bn;
        WCU->buttonsdown += bn;
        Gbuttonsdown += bn;
        break;
    default:
        return;
    }
    wi = gev.wi = widget - &Gwidgets[0];
    Gpopdownflag = FALSE;
    if (WCU->func)
        (*WCU->func) (&gev);
    if (Gpopdownflag) {
        Gpopdownflag = FALSE;
        if (gev.code == G_DOWN) {
            gev.code = G_UP;
            widget = &Gwidgets[wi];
            WCU->bstate[gev.data] = 0;
            WCU->buttonsdown--;
            Gbuttonsdown--;
            if (widget->inuse && WCU->func)
                (*WCU->func) (&gev);
        }
    }
}
