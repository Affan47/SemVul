find_home ( pacmangamestruct *pp, ghoststruct *g ){
    int i;
    int r,c;
    int cx, cy;
    ghoststruct *tmp_ghost;
    tmp_ghost = (ghoststruct*)malloc(sizeof ( ghoststruct ));
    if ( tmp_ghost == NULL ){
        fprintf(stderr, "find_home : Could not allocate memory.");
        exit ( 1 );
    }
    tmp_ghost = memmove(tmp_ghost, g, sizeof ( ghoststruct ));
    if ( tmp_ghost == NULL ){
        fprintf(stderr, "find_home : Could not copy memory.");
        exit ( 1 );
    }
    clear_trace ( tmp_ghost );
    clear_dir ( tmp_ghost );
    r = tmp_ghost->row;
    c = tmp_ghost->col;
    if ( ! recur_back_track ( pp, tmp_ghost, r, c ) ){
        fprintf(stderr, "Could not find way home.#@$?\n");
        pacman_get_jail_opening ( &cx, &cy);
        fprintf(stderr, "Jail was at (%d%d)\n", cx,cy);
    }
    for ( i = 0; i < GHOST_TRACE; i++ ){
        g->way_home[i].vx = tmp_ghost->way_home[i].vx;
        g->way_home[i].vy = tmp_ghost->way_home[i].vy;
    }
    g->home_count = tmp_ghost->home_count;
    g->home_idx = tmp_ghost->home_count;
    free(tmp_ghost);
}
