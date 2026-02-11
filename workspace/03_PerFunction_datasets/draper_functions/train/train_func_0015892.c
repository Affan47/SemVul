cpool_get_rand(int *s) {
    unsigned int start, i;
    struct CP_ENTRY *cpe;

    if(cp->alive) {
	start = rand() % cp->entries;
	for(i=0; i<cp->entries; i++) {
	    cpe = &cp->pool[(i+start) % cp->entries];
	    if(cpe->dead) continue;
	    if(cpe->local && cp->local_cpe && !cp->local_cpe->dead)
		cpe = cp->local_cpe;
	    if((*s = nc_connect_entry(cpe)) == -1) {
		cpe->dead = 1;
		continue;
	    }
	    return cpe;
	}
    }
    pthread_cond_signal(&mon_cond);
    return NULL;
}
