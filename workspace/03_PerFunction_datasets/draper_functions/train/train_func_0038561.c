random_teleport_level()
{
	int nlev, max_depth, min_depth,
	    cur_depth = (int)depth(&u.uz);

	if (!rn2(5) || Is_knox(&u.uz))
	    return cur_depth;


	min_depth = In_quest(&u.uz) ? dungeons[u.uz.dnum].depth_start : 1;
	max_depth = dunlevs_in_dungeon(&u.uz) +
			(dungeons[u.uz.dnum].depth_start - 1);

	if (Inhell && !u.uevent.invoked) max_depth -= 1;


	nlev = rn2(cur_depth + 3 - min_depth) + min_depth;
	if (nlev >= cur_depth) nlev++;

	if (nlev > max_depth) {
	    nlev = max_depth;

	    if (Is_botlevel(&u.uz)) nlev -= rnd(3);
	}
	if (nlev < min_depth) {
	    nlev = min_depth;
	    if (nlev == cur_depth) {
	        nlev += rnd(3);
	        if (nlev > max_depth)
		    nlev = max_depth;
	    }
	}
	return nlev;
}
