addIntersections(LineIntersector *li, int segmentIndex, int geomIndex)
{
#if GEOS_DEBUG
	cerr<<"["<<this<<"] Edge::addIntersections("<<li->toString()<<", "<<segmentIndex<<", "<<geomIndex<<") called"<<endl;
#endif
	for (int i=0; i<li->getIntersectionNum();i++) {
		addIntersection(li,segmentIndex,geomIndex,i);
	}

	testInvariant();
}
