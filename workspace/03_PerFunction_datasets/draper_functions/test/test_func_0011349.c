GMenuDrawLines(struct gmenu *m, int ln, int cnt) {
    GRect r, old1, old2, winrect;

    winrect.x = 0; winrect.width = m->width; winrect.y = 0; winrect.height = m->height;
    r = winrect; r.height = cnt*m->fh;
    r.y = (ln-m->offtop)*m->fh+m->bp;
    GDrawPushClip(m->w,&r,&old1);
    GBoxDrawBackground(m->w,&winrect,m->box,gs_active,false);
    GBoxDrawBorder(m->w,&winrect,m->box,gs_active,false);
    r.x = m->tickoff; r.width = m->rightedge-r.x;
    GDrawPushClip(m->w,&r,&old2);
    cnt += ln;
    for ( ; ln<cnt; ++ln )
	GMenuDrawMenuLine(m, &m->mi[ln], m->bp+(ln-m->offtop)*m->fh,m->w);
    GDrawPopClip(m->w,&old2);
    GDrawPopClip(m->w,&old1);
}
