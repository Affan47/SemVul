kill_city(city_info_t *cityp)
{
    view_map_t *vmap;
    piece_info_t *p;
    piece_info_t *next_p;
    piece_info_t **list;
    int i;


    for (p = map[cityp->loc].objp; p; p = next_p) {
	next_p = p->loc_link.next;

	if (p->type == ARMY) kill_obj (p, cityp->loc);
	else if (p->type != SATELLITE) {
	    if (p->type == TRANSPORT) {
		list = LIST(p->owner);

		while (p->cargo != NULL)
		    kill_one (list, p->cargo);
	    }
	    list = LIST (p->owner);
	    UNLINK (list[p->type], p, piece_link);
	    p->owner = (p->owner == USER ? COMP : USER);
	    list = LIST (p->owner);
	    LINK (list[p->type], p, piece_link);

	    p->func = NOFUNC;
	}
    }

    if (cityp->owner != UNOWNED) {
	vmap = MAP(cityp->owner);
	cityp->owner = UNOWNED;
	cityp->work = 0;
	cityp->prod = NOPIECE;

	for (i = 0; i < NUM_OBJECTS; i++)
	    cityp->func[i] = NOFUNC;

	scan (vmap, cityp->loc);
    }
}
