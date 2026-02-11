mouse_watch(panel *p)
{
    gint x, y;

    ENTER;
    gdk_display_get_pointer(gdk_display_get_default(), NULL, &x, &y, NULL);


    gint cx, cy, cw, ch;

    cx = p->cx;
    cy = p->cy;
    cw = p->aw;
    ch = p->ah;


    if (p->ah_state == ah_state_hidden) {
        switch (p->edge) {
        case EDGE_LEFT:
            cw = GAP;
            break;
        case EDGE_RIGHT:
            cx = cx + cw - GAP;
            cw = GAP;
            break;
        case EDGE_TOP:
            ch = GAP;
            break;
        case EDGE_BOTTOM:
            cy = cy + ch - GAP;
            ch = GAP;
            break;
       }
    }
    p->ah_far = ((x < cx) || (x > cx + cw) || (y < cy) || (y > cy + ch));

    p->ah_state(p);
    RET(TRUE);
}
