mkstairs(x, y, up, croom)
xchar x, y;
char  up;
struct mkroom *croom;
{
	if (!x) {
	    impossible("mkstairs:  bogus stair attempt at <%d,%d>", x, y);
	    return;
	}


	if ((dunlev(&u.uz) == 1 && up) ||
			(dunlev(&u.uz) == dunlevs_in_dungeon(&u.uz) && !up))
	    return;

	if(up) {
		xupstair = x;
		yupstair = y;
		upstairs_room = croom;
	} else {
		xdnstair = x;
		ydnstair = y;
		dnstairs_room = croom;
	}

	levl[x][y].typ = STAIRS;
	levl[x][y].ladder = up ? LA_UP : LA_DOWN;
}
