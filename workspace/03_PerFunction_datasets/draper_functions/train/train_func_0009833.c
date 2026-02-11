GetRelative(IntCoord& x, IntCoord& y, Interactor* rel) const {

    IntCoord left, bottom;
    GetPosition(left, bottom);
    x += left;
    y += bottom;

    if (rel != nil) {

	IntCoord rel_left, rel_bottom;
	rel->GetPosition(rel_left, rel_bottom);
	x -= rel_left;
	y -= rel_bottom;
    }
}
