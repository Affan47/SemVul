user_dir_ship(piece_info_t *obj, loc_t loc)
{
    if (map[loc].contents == MAP_CITY) {
	(void) sprintf (jnkbuf, "Your %s broke up on shore.",
			piece_attr[obj->type].name);

	fatal (obj, loc,
	       "That's never worked before, sir.  Do you really want to try? ",
	       jnkbuf);
    }

    else if (map[loc].contents == MAP_LAND) {
	bool enemy_killed = false;

	if (!getyn ("Ships need sea to float, sir.  Do you really want to go ashore? ")) return;

	if (user_map[loc].contents == MAP_LAND)
	{
	    comment ("Your %s broke up on shore.", piece_attr[obj->type].name);
	    ksend ("Your %s broke up on shore.", piece_attr[obj->type].name);
	}
	else {
	    enemy_killed = islower (user_map[loc].contents);
	    attack (obj, loc);

	    if (obj->hits > 0)
	    {
		comment ("Your %s breaks up after its successful assault.", piece_attr[obj->type].name);
		ksend ("Your %s breaks up after its successful assault.", piece_attr[obj->type].name);
	    }
	}
	if (obj->hits > 0) {
	    kill_obj (obj, loc);
	    if (enemy_killed)
		scan (comp_map, loc);
	}
    }

    else if (isupper (user_map[loc].contents)) {
	if (!getyn (
		"Sir, those are our men!  Do you really want to attack them? "))
	    return;

	attack (obj, loc);
    }

    else attack (obj, loc);
}
