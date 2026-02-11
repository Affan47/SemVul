draw_client_map(object *pl) {
    int i, j;
    sint16 ax, ay;
    int mflags;
    mapstruct *m, *pm;
    int min_x, min_y, max_x, max_y;

    if (pl->type != PLAYER) {
        LOG(llevError, "draw_client_map called with non player/non eric-server\n");
        return;
    }

    if (pl->contr->transport) {
        pm = pl->contr->transport->map;
    } else
        pm = pl->map;


    if (pm == NULL || pm->in_memory != MAP_IN_MEMORY)
        return;


    min_x = pl->x-pl->contr->socket.mapx/2;
    min_y = pl->y-pl->contr->socket.mapy/2;
    max_x = pl->x+(pl->contr->socket.mapx+1)/2;
    max_y = pl->y+(pl->contr->socket.mapy+1)/2;
    for (j = min_y; j < max_y; j++) {
        for (i = min_x; i < max_x; i++) {
            ax = i;
            ay = j;
            m = pm;
            mflags = get_map_flags(m, &m, ax, ay, &ax, &ay);
            if (mflags&P_OUT_OF_MAP)
                continue;
            if (mflags&P_NEED_UPDATE)
                update_position(m, ax, ay);


            if (mflags&P_NEW_MAP)
                m->timeout = 50;
        }
    }


    if (pl->contr->do_los) {
        update_los(pl);
        pl->contr->do_los = 0;
    }

    draw_client_map2(pl);
}
