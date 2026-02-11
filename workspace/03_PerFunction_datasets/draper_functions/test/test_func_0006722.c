f_intersects (BoxObj& userb, Graphic* gs) {
    Coord* convx, *convy;
    BoxObj b;
    boolean result = false;
    getBox(b, gs);

    if (b.Intersects(userb)) {
	convx = new Coord[count()+1];
	convy = new Coord[count()+1];
	transformList(x(), y(), count(), convx, convy, gs);
	FillPolygonObj fp (convx, convy, count());
	result = fp.Intersects(userb);
	delete convx;
	delete convy;
    }
    return result;
}
