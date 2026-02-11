produce(city_info_t *cityp)
{
    piece_info_t **list;
    piece_info_t *new;

    list = LIST (cityp->owner);

    cityp->work -= piece_attr[(int)cityp->prod].build_time;

    ASSERT (free_list);
    new = free_list;
    UNLINK (free_list, new, piece_link);
    LINK (list[(int)cityp->prod], new, piece_link);
    LINK (map[cityp->loc].objp, new, loc_link);
    new->cargo_link.next = NULL;
    new->cargo_link.prev = NULL;

    new->loc = cityp->loc;
    new->func = NOFUNC;
    new->hits = piece_attr[(int)cityp->prod].max_hits;
    new->owner = cityp->owner;
    new->type = cityp->prod;
    new->moved = 0;
    new->cargo = NULL;
    new->ship = NULL;
    new->count = 0;
    new->range = piece_attr[(int)cityp->prod].range;

    if (new->type == SATELLITE) {
	new->func = sat_dir[irand (4)];
    }
}
