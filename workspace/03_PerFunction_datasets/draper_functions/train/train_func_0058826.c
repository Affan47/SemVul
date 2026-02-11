scrollTick() {
    if (d->dx == 0 && d->dy == 0) {
        d->stopScrolling();
        return;
    }

    if (d->steps < 1) d->steps = 1;
    int takesteps = d->smoothScrollStopwatch.restart() / sSmoothScrollTick;
    int scroll_x = 0;
    int scroll_y = 0;
    if (takesteps < 1) takesteps = 1;
    if (takesteps > d->steps) takesteps = d->steps;
    for(int i = 0; i < takesteps; i++) {
        int ddx = (d->dx / (d->steps+1)) * 2;
        int ddy = (d->dy / (d->steps+1)) * 2;


        if (abs(ddx) > abs(d->dx)) ddx = d->dx;
        if (abs(ddy) > abs(d->dy)) ddy = d->dy;


        d->dx -= ddx;
        d->dy -= ddy;
        scroll_x += ddx;
        scroll_y += ddy;
        d->steps--;
    }

    d->shouldSmoothScroll = false;
    scrollContentsBy(scroll_x, scroll_y);

    if (takesteps < 2) {
        d->smoothScrollMissedDeadlines = 0;
    } else {
        if (d->smoothScrollMissedDeadlines != sWayTooMany &&
                (!m_part->xmlDocImpl() || !m_part->xmlDocImpl()->parsing())) {
            d->smoothScrollMissedDeadlines++;
            if (d->smoothScrollMissedDeadlines >= sMaxMissedDeadlines) {


                d->smoothScrollMissedDeadlines = sWayTooMany;
            }
        }
    }
}
