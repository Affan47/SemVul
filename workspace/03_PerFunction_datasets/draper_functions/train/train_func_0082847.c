GetCoords(int *x, int *y)
{
	int rval = CIE_GC_NONE_SET;
	if (Coords[0]!=INT_MAX && x!=NULL) {
		*x=Coords[0];
		rval |= CIE_GC_X_SET;
	}
	if (Coords[1]!=INT_MAX && x!=NULL) {
		*y=Coords[1];
		rval |= CIE_GC_Y_SET;
	}

	return rval;
}
