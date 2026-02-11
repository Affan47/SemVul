getInteriorPoint() const
{
	Coordinate interiorPt;
	int dim=getDimension();
	if (dim==0) {
		InteriorPointPoint intPt(this);
		if ( ! intPt.getInteriorPoint(interiorPt) ) return NULL;
	} else if (dim==1) {
		InteriorPointLine intPt(this);
		if ( ! intPt.getInteriorPoint(interiorPt) ) return NULL;
	} else {
		InteriorPointArea intPt(this);
		if ( ! intPt.getInteriorPoint(interiorPt) ) return NULL;
	}
	Point *p=getFactory()->createPointFromInternalCoord(&interiorPt, this);
	return p;
}
