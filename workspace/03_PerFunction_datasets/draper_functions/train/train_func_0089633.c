computeProperIntersectionIM(SegmentIntersector *intersector,IntersectionMatrix *imX)
{

	int dimA=(*arg)[0]->getGeometry()->getDimension();
	int dimB=(*arg)[1]->getGeometry()->getDimension();
	bool hasProper=intersector->hasProperIntersection();
	bool hasProperInterior=intersector->hasProperInteriorIntersection();


	if (dimA==2 && dimB==2) {
		if (hasProper) imX->setAtLeast("212101212");
	}


	 else if (dimA==2 && dimB==1) {
		if (hasProper) imX->setAtLeast("FFF0FFFF2");
		if (hasProperInterior) imX->setAtLeast("1FFFFF1FF");
	} else if (dimA==1 && dimB==2) {
		if (hasProper) imX->setAtLeast("F0FFFFFF2");
		if (hasProperInterior) imX->setAtLeast("1F1FFFFFF");
	}


	else if (dimA==1 && dimB==1) {
		if (hasProperInterior) imX->setAtLeast("0FFFFFFFF");
	}
}
