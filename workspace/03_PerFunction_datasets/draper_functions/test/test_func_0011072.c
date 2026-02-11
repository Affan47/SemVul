place(double ox, double oy, int orientation)
{
	beginPlace(ox, oy, orientation);

	if (orientation == kLeftRight) {
		fSchema1->place(ox, oy, orientation);
		fSchema2->place(ox, oy+fSchema1->height(), orientation);
	} else {
		fSchema2->place(ox, oy, orientation);
		fSchema1->place(ox, oy+fSchema2->height(), orientation);
	}

	endPlace();
}
