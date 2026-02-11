init_game(void)
{
    void make_map(void), place_cities(void);

    count_t i;

    kill_display ();
    automove = false;
    resigned = false;
    debug = false;
    print_debug = false;
    print_vmap = false;
    trace_pmap = false;
    save_movie = false;
    win = no_win;
    date = 0;
    user_score = 0;
    comp_score = 0;

    for (i = 0; i < MAP_SIZE; i++) {
	user_map[i].contents = ' ';
	user_map[i].seen = 0;
	comp_map[i].contents = ' ';
	comp_map[i].seen = 0;
    }
    for (i = 0; i < NUM_OBJECTS; i++) {
	user_obj[i] = NULL;
	comp_obj[i] = NULL;
    }
    free_list = NULL;
    for (i = 0; i < LIST_SIZE; i++) {
	piece_info_t *obj = &(object[i]);
	obj->hits = 0;
	obj->owner = UNOWNED;
	LINK (free_list, obj, piece_link);
    }

    make_map ();

    do {
	for (i = 0; i < MAP_SIZE; i ++) {
	    if (map[i].contents == MAP_CITY)
		map[i].contents = MAP_LAND;
	}
	place_cities ();
    } while
	(!select_cities ());
}
