OnMove(int dx, int dy)
{
	Coords[0]+=dx;
	Coords[1]+=dy;
	Coords[2]+=dx;
	Coords[3]+=dy;
	ChildCoords[0]+=dx;
	ChildCoords[1]+=dy;
	ChildCoords[2]+=dx;
	ChildCoords[3]+=dy;

	for (GUIObject *cgp = (GUIObject*)GET_FIRST(&Children); cgp != END_OF_LIST(&Children); cgp = (GUIObject*)GET_NEXT(cgp)) {
		cgp->OnMove(dx, dy);
	}

	DoMove(dx, dy);
}
