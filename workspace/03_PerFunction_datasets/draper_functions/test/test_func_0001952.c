mkcavearea(bool rockit)
{
    int dist;
    xchar xmin = u.ux, xmax = u.ux;
    xchar ymin = u.uy, ymax = u.uy;
    xchar i;
    bool waslit = rm_waslit();

    if (rockit) pline("Crash!  The ceiling collapses around you!");
    else pline("A mysterious force %s cave around you!",
               (levl[u.ux][u.uy].typ == CORR) ? "creates a" : "extends the");
    display_nhwindow(WIN_MESSAGE, true);

    for(dist = 1; dist <= 2; dist++) {
        xmin--; xmax++;


        if (dist < 2) {
            ymin--; ymax++;
            for(i = xmin+1; i < xmax; i++) {
                mkcavepos(i, ymin, dist, waslit, rockit);
                mkcavepos(i, ymax, dist, waslit, rockit);
            }
        }


        for(i = ymin; i <= ymax; i++) {
            mkcavepos(xmin, i, dist, waslit, rockit);
            mkcavepos(xmax, i, dist, waslit, rockit);
        }

        flush_screen(1);
        nh_delay_output();
    }

    if (!rockit && levl[u.ux][u.uy].typ == CORR) {
        levl[u.ux][u.uy].typ = ROOM;
        if (waslit) levl[u.ux][u.uy].waslit = true;
        newsym(u.ux, u.uy);
    }

    vision_full_recalc = 1;
}
