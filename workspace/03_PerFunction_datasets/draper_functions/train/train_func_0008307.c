gdnsd_rand_init(void) {
    unsigned throw_away;
    gdnsd_rstate_t* newstate = calloc(1, sizeof(gdnsd_rstate_t));
    pthread_mutex_lock(&rand_init_lock);
    newstate->x = gdnsd_rand_get64(&rand_init_state);
    newstate->y = gdnsd_rand_get64(&rand_init_state);
    newstate->z1 = gdnsd_rand_get32(&rand_init_state);
    newstate->c1 = gdnsd_rand_get32(&rand_init_state);
    newstate->z2 = gdnsd_rand_get32(&rand_init_state);
    newstate->c2 = gdnsd_rand_get32(&rand_init_state);
    throw_away  = gdnsd_rand_get64(&rand_init_state);
    pthread_mutex_unlock(&rand_init_lock);
    throw_away &= THROW_MASK;
    throw_away += THROW_MIN;
    while(throw_away--)
        gdnsd_rand_get64(newstate);
    return newstate;
}
